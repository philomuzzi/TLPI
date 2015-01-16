#include <pwd.h>

extern "C" {
    #include "tlpi_hdr.h"
}

int main(int argc, char const *argv[])
{
    struct passwd *pwd;

    while ((pwd = getpwent()) != NULL)
        printf("%-8s %ld\n", pwd->pw_name, (long)pwd->pw_uid);

    endpwent();

    return 0;
}