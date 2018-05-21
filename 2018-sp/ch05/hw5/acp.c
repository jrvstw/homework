#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFSIZE 4096

int main(int argc, char **argv)
{
    int inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        printf("error opening %s\n", argv[1]);
        exit(1);
    }

    char tmpName[] = "tmp_XXXXXX";
    mktemp(tmpName);
    int outputFd = open(tmpName, O_WRONLY | O_CREAT, 0644);
    if (outputFd == -1) {
        printf("error opening %s\n", tmpName);
        exit(1);
    }

    char buf[BUFFSIZE];
    ssize_t numIn, numOut;
    while ((numIn = read(inputFd, buf, BUFFSIZE)) > 0) {
        numOut = write(outputFd, buf, numIn);
        if (numIn != numOut) {
            printf("error. numIn != numOut\n");
            exit(1);
        }
    }

    printf("tmpFile name: %s\nPress Enter to continue.\n", tmpName);
    getchar();

    rename(tmpName, argv[2]);

    close(inputFd);
    close(outputFd);
    return 0;
}
