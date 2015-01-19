#include <sys/time.h>
#include <time.h>

extern "C" {
    #include "tlpi_hdr.h"
}

int main(int argc, char **argv)
{
    struct timeval tv;
    if (0 == gettimeofday(&tv, NULL))
    {
        errExit("gettimeofday");
    }

    printf("current time seconds: %d, usec: %ld\n", tv.tv_sec, tv.tv_usec);

    time_t tt;
    tt = time(NULL);

    printf("current time seconds: %d\n", tt);

    return 0;
}