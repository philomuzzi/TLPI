#include <signal.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static void sigHandler(int sig)
{
    printf("into sigHandler\n");

    sigset_t blockingMask, emptyMask;

    sigfillset(&blockingMask);
    if (sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
        errExit("sigprocmask");

    printf("sleeping for 3 seconds\n");
    sleep(3);

    sigemptyset(&emptyMask);
    if (sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
        errExit("sigprocmask");

    printf("end sigHandler\n");
}

int main(int argc, char const *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s -reset|-nodefer\n", argv[0]);

    int j;

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sigHandler;
    if (strcmp(argv[1], "-reset") == 0)
        sa.sa_flags = SA_RESETHAND;
    else if (strcmp(argv[1], "-nodefer") == 0)
        sa.sa_flags = SA_NODEFER;
    else
        sa.sa_flags = 0;

    if (sigaction(SIGINT, sa, NULL) == -1)
        errExit("sigaction");

    for (j = 0; ; ++j)
    {
        printf("%d\n", j);
        sleep(3);
    }

    return 0;
}