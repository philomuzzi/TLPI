#include <pthread.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static void* threadFunc(void *arg)
{
    char *s = (char *)arg;
    printf("%s\n", arg);

    pthread_join(pthread_self(), NULL);

    return (void *)strlen(s);
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    void *res;
    int s;

    s = pthread_create(&tid, NULL, threadFunc, "Hello World\n");
    if (s == -1)
        errExitEN(s, "pthread_create");

    printf("main thread\n");

    return 0;
}