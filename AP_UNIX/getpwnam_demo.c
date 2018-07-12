#include <sys/types.h>
#include <pwd.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

struct passwd *
getpwname(const char *name)
{
    struct passwd *ptr;
    
    setpwent();
    while((ptr = getpwent()) != NULL) {
        if (strcmp(name, ptr->pw_name) == 0)
            break;
    }
    endpwent();
    return (ptr);
}

void main(void)
{
    struct passwd *ptr = NULL;

    ptr = getpwname("philip");
    printf("%s:%s:%d\n",ptr->pw_name, ptr->pw_passwd, ptr->pw_uid);
}
