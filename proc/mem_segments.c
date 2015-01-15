#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];
int primes[] = {2, 3, 5, 7};

static int square(int x)
{
    int result;
    result = x * x;
    return result;
}

static void doCalc(int val)
{
    printf("The Square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;
        t = val * val * val;

        printf("the cube of %d is %d\n", val, t);
    }
}

int main(int argc, char **argv)
{
    static int key = 9973;
    static char mbuf[1024000];

    char *p;

    p = malloc(1024);

    doCalc(key);

    exit(EXIT_SUCCESS;
}