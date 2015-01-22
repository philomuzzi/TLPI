#include <signal.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static void sigHandler(int sig)
{
    printf("Ouch! sig: %d\n", sig);
}

int main(int argc, char** argv)
{
    int j;

    if (signal(SIGINT, sigHandler) == SIG_ERR)
        errExit("signal");

    for (j = 0; ; j++)
    {
        printf("%d\n", j);
        sleep(3);
    }

    return 0;
}