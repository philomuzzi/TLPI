#include <thread.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static int avail = 0;

static void* producerFunc(void *arg)
{
    int count = *((int *)arg);
    int s;
    while (count--) {
        s = pthread_mutex_lock(&mtx);
        if (s)
            errExitEN(s, "pthread_mutex_lock");

        avail++;
        printf("producer: add avail, %d\n", avail);

        s = pthread_mutex_unlock(&mtx);
        if (s)
            errExitEN(s, "pthread_mutex_unlock");
    }

    return NULL;
}

static void* consumerFunc(void *arg)
{
    int count = *((int *)arg);
    int s;

    while (count) {
        s = pthread_mutex_lock(&mtx);
        if (s)
            errExitEN(s, "pthread_mutex_lock");

        while (avail > 0)
        {
            printf("consumer: sub avail, %d\n", avail);
            avail--;
            count--;
        }

        s = pthread_mutex_unlock(&mtx);
        if (s)
            errExitEN(s, "pthread_mutex_unlock");
    }
}

int main(int argc, char const *argv[])
{
    int s;
    pthread_t t1, t2;
    int count = 100;

    s = pthread_create(&t1, NULL, producerFunc, &count);
    if (s)
        errExitEN(s, "pthread_create");

    s = pthread_create(&t2, NULL, consumerFunc, &count);
    if (s)
        errExitEN(s, "pthread_create");

    s = pthread_join(t1, NULL);
    if (s)
        errExitEN(s, "pthread_join");

    s = pthread_join(t2, NULL);
    if (s)
        errExitEN(s, "pthread_join");

    return 0;
}