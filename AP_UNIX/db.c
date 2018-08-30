#include    "db.h"
#include    <sys/uio.h>

/* Open or create a database. Same arguments as open(). */
DB *
db_open(const char *pathname, int oflag, int mode)
{
    DB      *db;
    int     i, len;
    char    asciiptr[PTR_SZ + 1],
            hash[(NHASH_DEF + 1) * PTR_SZ + 2];
            /* +2 for newline and null */
    struct stat statbuff;

        /* Allocate a DB structure, and the buffers it needs */
    len = strlen(pathname);
    if ((db = _db_alloc(len)) == NULL)
        err_dump("_db_alloc error for DB");

    db->oflag = oflag;  /* save a copy of the open flags */

        /* Open index file */
    strcpy(db->name, pathname);
    strcat(db->name, ".idx");
    if ((db->idxfd = open(db->name, oflag, mode)) < 0) {
        _db_free(db);
        return(NULL);
    }
        /* Open data file */
    strcpy(db->name + len, ".dat");
    if ((db->datfd = open(db->name, oflag, mode)) < 0) {
        _db_free(db);
        return (NULL);
    }
        
        /* If the database was created, we have to initialize it */
    if ((oflag & (O_CREAT | O_TRUNC)) == (O_CREAT | O_TRUNC)) {
        /* Write lock the entire file so that we can stat
         * the file, check its size, and initialize it,
         * as an atomic operation
         */
        if (writew_lock(db->idxfd, 0, SEEK_SET, 0) < 0)
            err_dump("writew_lock error");
        
        if (fstat(db->idxfd, &statbuff) < 0)
            err_sys("fstat error");
        if (statbuff.st_size == 0) {
            /* We have to build a list of (NHASH_DEF + 1) chain
             * ptrs with a value of 0. The +1 is for the free
             * list pointer that precedes the hash table.
             */
            sprintf(asciiptr, "%*d", PTR_SZ, 0);
            hash[0] = 0;
            for (i = 0; i < (NHASH_DEF + 1); i++)
                strcat(hash, asciiptr);
            strcat(hash, "\n");

            i = strlen(hash);
            if (write(db->idxfd, hash, i) != i)
                err_dump("write error initializing index file");
        }
        if (un_lock(db->idxfd, 0,  SEEK_SET, 0) < 0)
            err_dump("un_lock error");
    }
    db->nhash   = NHASH_DEF;  /* hash table size */
    db->hashoff = HASH_OFF; /* free list ptr always at FREE_OFF */

    db_rewind(db);
    return (db);
}


/* Allocate & initialize a DB structure, and all the buffers it needs */
DB *
_db_alloc(int namelen)
{
    DB      *db;
            /* Use calloc, to init structure to zero */
    if ((db = calloc(1, sizeof(DB))) == NULL)
        err_dump("calloc error for DB");

    db->idxfd = db->datfd = -1;     /* descriptors */

        /* Allocate room for the name.
         * +5 for ".idx" or ".dat" plus null at end .
         */
    if ((db->name = malloc(namelen + 5)) == NULL)
        err_dump("malloc error for name");

        /* Allocate an index buffer and a data buffer.
         * +2 for newline and null at end.
         */
    if ((db->idxbuf = malloc(IDXLEN_MAX + 2)) == NULL)
        err_dump("malloc error for index buffer");
    if ((db->datbuf = malloc(DATLEN_MAX + 2)) == NULL)
        err_dump("malloc error for data buffer");

    return (db);
}


/* Free up a DB structure, and all the malloc'ed buffers it
 * may point to. Also close the file descriptors if still open.
 */
int
_db_free(DB *db)
{
    if (db->idxfd >= 0 && close(db->idxfd) < 0)
        err_dump("index close error");
    if (db->datfd >= 0 && close(db->datfd) < 0)
        err_dump("data close error");
    db->idxfd = db->datfd = -1;

    if (db->idxbuf != NULL)
        free(db->idxbuf);
    if (db->datbuf != NULL)
        free(db->datbuf);
    if (db->name != NULL)
        free(db->name);
    free(db);
    return(0);
}

void
db_close(DB *db)
{
    _db_free(db);   /* close fds, free buffers & struct */
}

/* Fetch a specified record.
 * We return a pointer to the null-terminated data.
 */
char *
db_fetch(DB *db, const char *key)
{
    char    *ptr;
    if (_db_find(db, key, 0) < 0) {
        ptr = NULL;     /* error, record not found */
        db->cnt_fetcher++;
    } else {
        ptr = _db_readdat(db);  /* return pointer to data */
        db->cnt_fetchok++;
    }

        /* Unlock the hash chain that _db_find() locked */
    if (un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
        err_dump("un_lock error");
    return (ptr);
}

/* Find the specified record.
 * Called by db_delete(), db_fetch(), and db_store().
 */
int
_db_find(DB *db, const char *key, int writelock)
{
    off_t   offset, nextoffset;
        /* Calculate hash value for this key, then calculate byte
         * offset of corresponding chain ptr in hash table.
         * This is where our search starts.
         */

        /* calc offset in hash table for this key */
    db->chainoff = (_db_hash(db, key) * PTR_SZ) + db->hashoff;
    db->ptroff = db->chainoff;
        
        /* Here's where we lock this hash chain. It's the
         * caller's responsibility to unlock it when done.
         * Note we lock and unlock only the first byte.
         */
    if (writelock) {
        if (writew_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
            err_dump("writew_lock error");
        } else {
            if (readw_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
                err_dump("readw_lock error");
        }
            /* Get the offset in the index file of first record
             * on the hash chain (can be 0) 
             */
    offset = _db_readptr(db, db->ptroff);
    while (offset != 0) {
        nextoffset = _db_readidx(db, offset);
        if (strcmp(db->idxbuf, key) == 0)
            break;      /* found a match */
        db->ptroff = offset;    /* offset of this (unequal) record */
        offset = nextoffset;    /* next one to compare */
    }
    if (offset == 0)
        return (-1);    /* error, record not found */
        
        /* We have a match. We're guaranteed that db->ptroff contains
         * the offset of the chain ptr that points to this matching
         * index record. _db_dodelete() uses this fact. (The chain
         * ptr that points to this matching record could be in an
         * index record or in the hash table.) 
         */
    return (0);
}

/* Calculate the hash value for a key */
hash_t
_db_hash(DB *db, const char *key)
{
    hash_t      hval;
    const char  *ptr;
    char        c;
    int         i;

    hval = 0;
    for (ptr = key, i = 1; c = *ptr++; i++)
        hval += c * i;      /* ascii char times its 1-based index */

    return (hval % db->nhash);
}


/* Read a chain ptr field from anywhere in the index file:
 * the free list pointer, a hash table chain ptr, or an
 * index record chain ptr. 
 */
off_t
_db_readptr(DB *db, off_t offset)
{
    char    asciiptr[PTR_SZ + 1];

    if (lseek(db->idxfd, offset, SEEK_SET) == -1)
        err_dump("lseek error to ptr field");
    if (read(db->idxfd, asciiptr, PTR_SZ) != PTR_SZ)
        err_dump("read error of ptr field");

    asciiptr[PTR_SZ] = 0;      /* null terminate */
    return (atol(asciiptr));
}


/* Read the next index record. We start at the specified offset in
 * the index file. We read the index record into db->idxbuf and
 * replace the separators with null bytres. If all is OK we set
 * db->datoff and db-datlen to the offset and length of the
 * corresponding data record in the data file.
 */
off_t
_db_readidx(DB *db, off_t offset)
{
    int     i;
    char    *ptr1, *ptr2;
    char    asciiptr[PTR_SZ + 1], asciilen[IDXLEN_SZ + 1];
    struct iovec    iov[2];

        /* Position index file and record the offset. db_nextrec()
         * calls us with offset==0, meaning read from current offset.
         * We still need to call lseek() to record the current offset.
         */
    if ((db->idxoff = lseek(db-idxfd, offset,
                    offset == 0 ? SEEK_CUR : SEEK_SET)) == -1)
        err_dump("lseek error");
    /* Read the ascii chain ptr and the ascii length at
     * the front of the index record. This tells us the
     * remaining size of the index record 
     */
    iov[0].iov_base = asciiptr;
    iov[0].iov_len = PTR_SZ;
    iov[1].iov_base = assiilen;
    iov[1].iov_len = IDXLEN_SZ;
    if ((i = readv(db->idxfd, &iov[0], 2)) != PTR_SZ + IDXLEN_SZ) {
        if (i == 0 && offset == 0)
            return(-1);     /* EOF for db_nextrec() */
        err_dump("readv error of index record");
    }
    asciiptr[PTR_SZ] = 0;   /* null terminate */
    db->ptrval = atol(asciiptr);    /* offset of next key in chain */
                    /* this is our return value; always >= 0 */
    asciilen[IDXLEN_SZ] = 0;    /* null terminate */
    if ((db->idxlen = atoi(asciilen)) < IDXLEN_MIN ||
            db->idxlen > IDXLEN_MAX)
        err_dump("invalid length");
        /* Now read the actual index record. We read it into the key 
         * buffer that we malloced when we opened the database.
         */
    if ((i = read(db->idxfd, db->idxbuf, db->idxlen)) != db->idxlen)
        err_dump("read error of index record");
    if (db->idxbuf[db->idxlen-1] != '\n')
        err_dump("missing newline");    /* sanity checks */
    db->idxbuf[db->idxlen-1] = 0;       /* replace newline with null */

        /* Find the separators in the index record */
    if ((ptr1 = strchr(db->idxbuf, SEP)) == NULL)
        err_dump("missing first separator");
    *ptr1++ = 0;    /* replace SEP with null */
    if ((ptr2 = strchr(ptr1, SEP)) == NULL)
        err_dump("missing second separator");
    *ptr2++ = 0;    /* replace SEP with null */

    if (strchr(ptr2, SEP) != NULL)
        err_dump("too many separators");

        /* Get the starting offset and length of the data record */
    if ((db->datoff = atol(ptr1)) < 0)
        err_dump("starting offset < 0");
    if ((db->datlen = atol(ptr2)) <= 0 || db->datlen > DATLEN_MAX)
        err_dump("invalid length");
    return(db->ptrval);     /* return offset of next key in chain */
}


/* Read the current data record into the data buffer.
 * Return a pointer to the null-terminated data buffer.
 */
char *
_db_readdat(DB *db)
{
    if (lseek(db->datfd, db->datoff, SEEK_SET) == -1)
        err_dump("lseek error");

    if (read(db->datfd, db->datbuf, db->datlen) != db->datlen)
        err_dump("read error");
    if (db->datbuf[db->datlen - 1] != '\n')    /* sanity check */
        err_dump("missing newline");
    db->datbuf[db->datlen - 1] = 0;     /* replace newline with null */

    return (db->datbuf);    /* return pointer to data record */
}

/* Delete the specified record */
int
db_delete(DB *db, const char *key)
{
    int     rc;

    if  (_db_find(db, key, 1) == 0) {
        rc = _db_dodelete(db);  /* record found */
        db->cnt_delok++;
    } else {
        rc = -1;        /* not found */
        db->cnt_delerr++;
    }
    if (un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
        err_dump("un_lock error");
    return(rc);
}

/* Delete the current record specified by the DB structure.
 * This function is called by db_delete() and db_store(),
 * after the record has been located by _db_find(). 
 */
int
_db_dodelete(DB *db)
{
    int     i;
    char    *ptr;
    off_t   freeptr, saveptr;

            /* Set data buffer to all blanks */
    for (ptr = db->datbuf, i = 0; i < db->datlen - 1; i++)
        *ptr++ = ' ';
    *ptr = 0;   /* null terminate for _db_writedat() */

        /* Set key to blanks */
    ptr = db->idxbuf;
    while (*ptr)
        *ptr++ = ' ';

        /* We have to lock the free list */
    if (writew_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
        err_dump("writew_lock error");

    /* Write the data record with all blanks */
    _db_writedat(db, db->datbuf, db->datoff, SEEK_SET);

    /* Read the free list pointer. Its value becomes the
     * chain ptr field of the deleted index record. This means
     * the deleted record becomes the head of the free list.
     */
    freeptr = _db_readptr(db, FREE_OFF);

        /* Save the contents of index record chain ptr,
         * before it's rewritten by _db_writeidx().
         */
    saveptr = db->ptrval;
        
        /* Rewrite the index record. This also rewrites the length
         * of the index record, the data offset, and the data length,
         * none of which has changed, buf that's OK.
         */
    _db_writeidx(db, db->idxbuf, db->idxoff, SEEK_SET, freeptr);

        /* Write the new free list pointer */
    _db_writeptr(db, FREE_OFF, db->idxoff);

        /* Rewrite the chain ptr that pointed to this record
         * being deleted. Recall that _db_find() sets db->ptroff
         * to point to this chain ptr. We set this chain ptr
         * to the contents of the deleted record's chain ptr,
         * saveptr, which can be either zero or nonzero.
         */
    _db_writeptr(db, db->ptroff, saveptr);
    if (un_lock(db->idxfd, FREE_OFF, SEEK_SET, 1) < 0)
        err_dump("un_lock error");

    return (0);
}


/* Write a data record. Called by _db_dodelete() (to write
 * the record with blanks) and db_store().
 */
void
_db_writedat(DB *db, const char *data, off_t offset, int whence)
{
    struct iovec    iov[2];
    static char     newline = '\n';

        /* If we're appending, we have to lock before doing the lseek()
         * and write() to make the two an atomic operation. If we're
         * overwriting an existing record, we don't have to lock.
         */
    if (whence == SEEK_END) /* we're appending, lock entire file */
        if (writew_lock(db->datfd, 0, SEEK_SET, 0) < 0)
            err_dump("writew_lock error");

    if ((db->datoff = lseek(db->datfd, offset, whence)) == -1)
        err_dump("lseek error");
    db->datlen = strlen(data) + 1;   /* datlen includes newline */

    iov[0].iov_base = (char *) data;
    iov[0].iov_len = db->datlen - 1;
    iov[1].iov_base = &newline;
    iov[1].iov_len = 1;
    if (writev(db->datfd, &iov[0], 2) != db->datlen)
        err_dump("writev error of data record");

    if (whence == SEEK_END)
        if (un_lock(db->datfd, 0, SEEK_SET, 0) < 0)
            err_dump("un_lock error");
}

/* Write an index record.
 * _db_writedat() is called before this function, to set the fields
 * datoff and datlen in the DB structure, which we need to write
 * the index record 
 */
void
_db_writeidx(DB *db, const char *key,
            off_t offset, int whence, off_t ptrval)
{
    struct iovec    iov[2];
    char            asciiptrlen[PTR_SZ + IDXLEN_SZ + 1];
    int             len;

    if ((db->ptrval = ptrval) < 0 || ptrval > PTR_MAX)
        err_quit("invalid ptr: %d", ptrval);

    sprintf(db->idxbuf, "%s%c%d%c%d\n",
            key, SEP, db->datoff, SEP, db->datlen);
    if ((len = strlen(db->idxbuf)) < IDXLEN_MIN || len > IDXLEN_MAX)
        err_dump("invalid length");
    sprintf(asciiptrlen, "%*.d%*d", PTR_SZ, ptrval, IDXLEN_SZ, len);

        /* If we're appending, we have to lock before doing the lseek()
         * and write() to make the two an atomic operation. If we're
         * overwriting an existing record, we don't have to lock.
         */
    if (whence == SEEK_END)     /* we're appending */
        if (writew_lock(db->idxfd, ((db->nhash+1)*PTR_SZ)+1,
                    SEEK_SET, 0) < 0)
            err_dump("writew_lock error");

        /* Position the index file and record the offset */
    if ((db->idxoff = lseek(db->idxfd, offset, whence)) == -1)
        err_dump("lseek error");

    iov[0].iov_base = asciiptrlen;
    iov[0].iov_len = PTR_SZ + IDXLEN_SZ;
    iov[1].iov_base = db->idxbuf;
    iov[1].iov_len = len;
    if (writev(db->idxfd, &iov[0], 2) != PTR_SZ + IDXLEN_SZ + len)
        err_dump("writev error of index record");

    if (whence == SEEK_END)
        if (un_lock(db->idxfd, ((db->nhash+1)*PTR_SZ)+1, SEEK_SET, 0) < 0)
            err_dump("un_lock error");
}


/* Write a chain ptr field somewhere in the index file:
 * the free list, the hash table, or in an index record
 */
void
_db_writeptr(DB *db, off_t offset, off_t ptrval)
{
    char    asciiptr[PTR_SZ + 1];

    if (ptrval < 0 || ptrval > PTR_MAX)
        err_quit("invalid ptr: %d", ptrval);
    sprintf(asciiptr, "%*d", PTR_SZ, ptrval);

    if (lseek(db->idxfd, offset, SEEK_SET) == -1)
        err_dump("lseek error to ptr field");
    if (write(db->idxfd, asciiptr, PTR_SZ) != PTR_SZ)
        err_dump("write error of ptr field");
}

    
