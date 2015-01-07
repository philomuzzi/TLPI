#include <fcntl.h>
extern "C"
{
    #include "tlpi_hdr.h"
}

int main(int argc, char** argv)
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    int fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR);
    int fd2 = dup(fd);
    int fd3 = open(argv[1], O_RDWR);

    write(fd, "Hello,", 6);
    write(fd2, "world", 6);
    lseek(fd2, 0, SEEK_SET);
    write(fd, "HELLO,",6);
    write(fd3, "Gidday", 6);

    char buf[100];
    read(fd, buf, 100);
    printf("file content: %s\n", buf);

    exit(EXIT_SUCCESS);
}
