#include <time.h>

extern "C" {
    #include "tlpi_hdr.h"
}

int main(int argc, char const *argv[])
{
    time_t tt, tt_c;
    struct tm ttm;

    ttm = gmtime(&tt);
    if (!ttm)
        errExit("gmtime");

    tt_c = mktime(&ttm);
    if (-1 == tt_c)
        errExit("mktime");

    printf("current_time seconds: %ld\n", tt_c);

    ttm = localtime(&tt);
    if (!ttm)
        errExit("localtime");

    tt_c = mktime(&ttm);
    if (-1 == tt_c)
        errExit("mktime");

    printf("current_time seconds: %ld\n", tt_c);

    char *tchar = asctime(&ttm);

    if (!tchar)
        errExit("asctime");

    printf("current_time: %s\n", tchar);

    return 0;
}