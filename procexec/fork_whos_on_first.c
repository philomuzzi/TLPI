#include <sys/wait.h>
extern "C" {
    #include "tlpi_hdr.h"
}

int main(int argc, char const *argv[])
{
    int numChildren;
    pid_t childPid;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [num-children]\n", argv[0]);

    numChildren = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-children") : 1;

    setbuf(stdout, NULL);

    for (int i = 0; i < numChildren; ++i)
    {
        switch(childPid = fork()) {
            case -1:
                errExit("fork");
            case 0:
                printf("%d child\n", i);
                _exit(EXIT_SUCCESS);
            default:
                printf("%d parent\n", i);
                wait(NULL);
                break;
        }
    }

    return 0;
}