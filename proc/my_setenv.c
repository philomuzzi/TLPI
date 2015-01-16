#include <stdlib.h>

extern "C" {
    #include "tlpi_hdr.h"
}

extern char** environ;

int my_setenv(cosnt char* name, const char *value, int override)
{
    if(getenv(name) && !override)
        return -1;

    int len = 0;
    len = strlen(name) + 1 + strlen(value) + 1;

    char *buf = (char*)malloc(len);
    memset(buf, 0, len);

    strncpy(buf, name, strlen(name));
    buf[strlen(name)] = "=";
    strncpy(buf+strlen(name)+1, value, strlen(value));

    if (putenv(buf))
        return -1

    return 0;
}

// 在env列表中找到=之前的名称对比，如果一致，将**ep=NULL
int my_unsetenv(const char* name)
{
    char **ep;

    for(ep = environ; *ep != NULL; ep++)
    {
        if (0 == strchr(*ep, name) && strcmp(*ep+strlen(name), "=") == 0)
        {
            ep = NULL;
        }
    }
}

int main(int argc, char const *argv[])
{
    int j;
    char **ep;

    clearenv();

    my_setenv("abc", "ced", 1);
    my_setenv("231", "def", 1);

    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);

    my_setenv("231", "zzz", 1);

    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);

    my_unsetenv("231");

    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);

    return 0;
}