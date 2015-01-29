#include <pthread.h>

extern "C" {
    #include "tpli_hdr.h"
}

static void* threadFunc(void *arg)
{
    int j;
    printf("New thread started\n");
    for (j = 1; ; j++)
    {
        printf("Loop %d\n", j);
        sleep(1);
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t t;
    int s;
    void *res;

    s = pthread_create(&t, NULL, threadFunc, NULL);
    if (s)
        errExitEN(s, "pthread_create");

    sleep(3);

    s = pthread_cancel(t);
    if (s)
        errExitEN(s, "pthread_cancel");

    s = pthread_join(t, &res);
    if (s)
        errExitEN(s, "pthread_join");

    if (res == PTHREAD_CANCELED)
        printf("Thread was canceled\n");
    else
        printf("Thread was not canceled, but should not be happened!\n");

    return 0;
}