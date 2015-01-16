#include <stdlib.h>

extern "C" {
    #include "tlpi_hdr.h"
}

int main(int argc, char *argv[])
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s \"env1=xxx\" ...\n", argv[0]);

    int j;
    char **ep;

    clearenv();

    for (j = 1; j < argc; ++j)
        if (putenv(argv[j]) != 0)
            errExit("putenv: %s", argv[j]);

    if (setenv("GREAT", "hello world", 0) == -1)
        errExit("setenv");

    unsetenv("BYE");

    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);

    return 0;
}
