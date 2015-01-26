#include <signal.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static void sigHandler(int sig)
{
    printf("sig id: %d, Ouch!\n", sig);
}

int main(int argc, char const *argv[])
{
    int j;

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    if (sigaction(SIGINT, sa, NULL) == -1)
        errExit("sigaction");

    for(j = 0; ; ++j)
    {
        printf("%d\n", j);
        sleep(3);
    }

    return 0;
}