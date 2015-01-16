#include <stdlib.h>

extern "C" {
    #include "tlpi_hdr.h"
}

extern char** environ;

int my_setenv(const char* name, const char *value, int override)
{
    if(getenv(name) && !override)
        return -1;

    int len = 0;
    len = strlen(name) + 1 + strlen(value) + 1;

    char *buf = (char*)malloc(len);
    memset(buf, 0, len);

    strncpy(buf, name, strlen(name));
    memset(buf+strlen(name), '=', 1);
    strncpy(buf+strlen(name)+1, value, strlen(value));

    if (putenv(buf))
        return -1;

    return 0;
}

// 在env列表中找到=之前的名称对比，如果一致，将**ep=NULL
int my_unsetenv(const char* name)
{
    if (!getenv(name))
        return -1;

    char **ep;
    char *chr;
    char **pos;

    for(ep = environ; *ep != NULL;)
    {
        chr = strstr(*ep, name);
        if (chr && (chr - *ep == 0) && strncmp(chr+strlen(name), "=", 1) == 0)
        {
            pos = ep;
            while(*(pos + 1) != NULL)
            {
                *pos = *(pos + 1);
                pos++;
            }
            *pos = NULL;
        }
        else
            ep++;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    char **ep;

    clearenv();

    my_setenv("abc", "ced", 1);
    my_setenv("231", "def", 1);
    my_setenv("098", "tre", 0);

    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);

    puts("");

    my_setenv("231", "zzz", 1);
    my_setenv("abc", "xxx", 0);

    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);

    puts("");

    my_unsetenv("231");

    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);

    puts("");

    return 0;
}
