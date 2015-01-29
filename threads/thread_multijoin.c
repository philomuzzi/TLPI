#include <thread.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int totThreads = 0;
static int numLive = 0;

static int numUnjoined = 0;

enum tstate {
    TS_ALIVE,
    TS_TERMINATED,
    TS_JOINED
};

static struct {
    pthread_t tid;
    enum tstate state;
    int sleepTime;
} *thread;

static void* threadFunc(void *arg)
{
    int idx = *((int *) arg);
    int s;
    sleep(thread[idx].sleepTime);
    printf("Thread %d terminated\n", idx);

    s = pthread_mutex_lock(&mtx);
    if (s)
        errExitEN(s, "pthread_mutex_lock");

    numUnjoined++;
    thread[idx].state = TS_TERMINATED;

    s = pthread_mutex_unlock(&mtx);
    if (s)
        errExitEN(s, "pthread_mutex_unlock");

    s = pthread_cond_signal(&cond);
    if (s)
        errExitEN(s, "pthread_cond_signal");

    return NULL;
}

int main(int argc, char const *argv[])
{
    int s, idx;
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s nsecs...\n", argv[0]);

    thread = calloc(argc - 1, sizeof(*thread));
    if (thread = NULL)
        errExit("calloc");

    for (idx = 0; i < argc - 1; idx++)
    {
        thread[idx].sleepTime = getInt(argv[idx+1], GN_NONNEG, NULL);
        thread[idx].state = TS_ALIVE;
        s = pthread_create(&thread[idx].tid, NULL, threadFunc, &idx);
        if (s)
            errExitEN(s, "pthread_create");
    }

    totThreads = argc - 1;
    numLive = totThreads;

    while (numLive > 0) {
        s = pthread_mutex_lock(&mtx);
        if (s)
            errExitEN(s, "pthread_mutex_lock");

        while (numUnjoined == 0)
        {
            s = pthread_cond_wait(&cond);
            if (s)
                errExitEN(s, "pthread_cond_wait");
        }

        while (numUnjoined > 0)
        {
            for (idx = 0; idx < totThreads; idx++)
            {
                if (thread[idx].state == TS_TERMINATED)
                {
                    s = pthread_join(thread[idx].tid, NULL);
                    if (s)
                        errExitEN(s, "pthread_join");

                    numLive--;
                    numUnjoined--;
                    thread[idx].tstate = TS_JOINED;

                    printf("Reaped thread %d (numLive=%d)\n", idx, numLive);
                }
            }
        }

        s = pthread_mutex_unlock(&mtx);
        if (s)
            errExitEN(s, "pthread_mutex_unlock");
    }

    return 0;
}