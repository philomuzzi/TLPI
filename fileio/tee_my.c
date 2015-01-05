#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
extern "C"
{
    #include "tlpi_hdr.h"
}

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char** argv)
{
    int ap = 1;
    int openFlags = O_RDWR | O_CREAT;
    char buf[BUF_SIZE];
    int numRead;
    int fileno[10];

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s [-a] file...\n", argv[0]);

    if (strcmp(argv[1], "-a") == 0)
    {
        openFlags |= O_APPEND;
        ap = 2;
    }

    for (int i = 0; ap < argc; ap++, i++)
    {
        int tmpfd = open(argv[ap], openFlags, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
        if (tmpfd == -1)
            errExit("open");
        fileno[i] = tmpfd;
    }

    memset(buf, 0, BUF_SIZE);
    while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        for(int i = 0; i < 10; ++i)
        {
            if (fileno[i] > 0) // check fd;
                if(write(tmpfd, buf, numRead) != numRead)
                    errExit("write");
        }
    }

    if (numRead == -1)
        errExit("read");

    exit(EXIT_SUCCESS);
}
