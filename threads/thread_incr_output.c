#include <thread.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static int glob = 0;

struct sarg{
    int loops;
    int mark;
};

static void * threadFunc(void *arg)
{
    sarg *sa = (sarg *)arg;
    int loc, j;

    for (j = 0; j < sa->loops; ++j)
    {
        loc = glob;
        loc++;
        glob = loc;

        printf("thread %d: glob value %d\n", sa->mark, glob);
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t t1, t2;
    int s, idx;
    sarg *arg;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s loops...\n", argv[0]);

    arg = calloc(argc - 1, sizeof(*arg));
    if (arg == NULL)
        errExit("calloc");

    for (idx = 0; idx < argc - 1; ++idx)
    {
        arg[idx].loops = getInt(argv[idx + 1], GN_GT_0, "num-loops");
        arg[idx].mark = idx;
    }

    s = pthread_create(&t1, NULL, threadFunc, arg[0])
    if (s != 0)
        errExitEN(s, "pthread_create");
    s = pthread_create(&t2, NULL, threadFunc, arg[0])
    if (s != 0)
        errExitEN(s, "pthread_create");

    s = pthread_join(t1, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    s = pthread_join(t2, NULL)
    if (s != 0)
        errExitEN(s, "pthread_join");

    printf("glob = %d\n", glob);
    return 0;
}