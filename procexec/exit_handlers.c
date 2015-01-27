#include <stdlib.h>
extern "C" {
    #include "tlpi_hdr.h"
}

static void atexitFunc1(void)
{
    printf("atexit function 1 called\n");
}

staic void atexitFunc2(void)
{
    printf("atexit function 2 called\n");
}

static void onexitFunc(int exitStatus, void *args)
{
    printf("on_exit function called: status=%d, arg=%ld\n", exitStatus, (long)args);
}

int main(int argc, char const *argv[])
{
    if (on_exit(onexitFunc, (void *)10) != 0)
        fatal("on_exit 1");
    if (atexit(atexitFunc1) != 0)
        fatal("at exit 1");
    if (atexit(atexitFunc2) != 0)
        fatal("at exit 2");
    if (on_exit(onexitFunc, (void *)20) != 0)
        fatal("on_exit 2");

    exit(2);
}