int main() {
    union
    {
        long l;
        char c[sizeof(long)];
    }u;
    u.l = 1;
    exit (u.c[sizeof(long) -1] == 1);
}

