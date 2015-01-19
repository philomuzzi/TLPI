#include <sys/time.h>
#include <time.h>

extern "C" {
    #include "tlpi_hdr.h"
}

int main(int argc, char **argv)
{
    struct timeval tv;
    if (-1 == gettimeofday(&tv, NULL))
    {
        errExit("gettimeofday");
    }

    printf("current time seconds: %ld, usec: %ld\n", tv.tv_sec, tv.tv_usec);

    time_t tt;
    tt = time(NULL);

    printf("current time seconds: %ld\n", tt);

    char * tchar = ctime(&tt);
    if (!tchar)
        errExit("ctime");

    printf("current time: %s", tchar);

    tchar = NULL;
    char buf[100];
    memset(buf, 0, 100);
    tchar = ctime_r(&tt, buf);
    if (!tchar)
        errExit("ctime_r");

    printf("current time: %s", buf);

    return 0;
}
