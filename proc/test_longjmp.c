// 测试longjmp进去已经返回的函数

#include <setjmp.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static jmp_buf env;

void doJmp()
{
    int i = 0;
    char *y = "xyz";
    printf("in doJmp: %d\n", i);
    printf("str y: %s\n", y);
    i = setjmp(env);
    if (i == 0)
    {
        printf("after first setjmp: %d\n", i);
        printf("str y: %s\n", y);
    }
    else
    {
        printf("after second setjmp: %d\n", i);
        // error
        printf("str y: %s\n", y);
    }
}

void follow()
{
    int x = 1, y = 3, z = 5;
    char *t = "qwert";
    printf("follow x: %d, y: %d, z:%d\n", x, y, z);
    printf("str t: %s\n", t);
}

int main(int argc, char const *argv[])
{
    bool bJmp = true;

    doJmp();
    follow();

    if(bJmp) {
        bJmp = false;
        longjmp(env, 1);
    }

    printf("main end\n");

    return 0;
}
