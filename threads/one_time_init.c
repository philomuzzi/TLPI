#include <pthread.h>

static struct {
    bool init;
    pthread_mutex_t mtx;
} *control;

#define init (void (*)(void *))

void one_time_init(control, init)
{

}

int main(int argc, char const *argv[])
{
    return 0;
}