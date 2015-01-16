// 测试longjmp进去已经返回的函数

#include <setjmp.h>

extern "C" {
    #include "tlpi_hdr.h"
}

static jmp_buf env;

void static doJmp()
{
    int i = 0;
    printf("in doJmp: %d\n", i);
    i = setjmp(env);
    if (i == 0)
        printf("after first setjmp: %d\n", i);
    else
        printf("after second setjmp: %d\n", i);
}

int main(int argc, char const *argv[])
{
    bool bJmp = true;

    doJmp();

    if(bJmp) {
        bJmp = false;
        longjmp(env, 1);
    }

    return 0;
}