extern "C" {
    ##include "tlpi_hdr.h"
}

extern char** environ;

int int main(int argc, char const *argv[])
{
    char *ep;
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    return 0;
}