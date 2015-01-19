#include <pwd.h>

extern "C" {
    #include "tlpi_hdr.h"
}

struct passwd *my_getpwnam(const char *name)
{
    struct passwd *pwd;
    setpwent();

    while ((pwd = getpwent()) != NULL)
    {
        printf("%-8s %ld\n", pwd->pw_name, (long)pwd->pw_uid);
        if (strcmp(pwd->pw_name, name) == 0)
            return pwd;
    }

    endpwent();

    return NULL;
}

int main(int argc, char **argv)
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s username\n", argv[0]);

    struct passwd *pwd;

    errno = 0;
    pwd = my_getpwnam(argv[1]);
    if (pwd == NULL) {
        if (errno == 0)
            fatal("not found user %s\n", argv[1]);
        else
            errExit("my_getpwnam");
    }

    printf("found user %s, uid is %ld", pwd->pw_name, (long)pwd->pw_uid);

    return 0;
}
