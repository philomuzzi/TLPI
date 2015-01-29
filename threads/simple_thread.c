#include <pthread.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static void* threadFunc(void *arg)
{
    char *s = (char *)arg;
    printf("%s\n", s);

    return (void *)strlen(s);
}

int main(int argc, char const *argv[])
{
    pthread_t t1;
    void *res;
    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello World\n");
    if (s != 0)
        errExitEN(s, "pthread_create");

    printf("Message from main()\n");
    s = pthread_join(t1, &res);
    if (s != 0)
        errExitEN(s, "pthread_join");

    printf("Thread returned %ld\n", (long)res);

    return 0;
}