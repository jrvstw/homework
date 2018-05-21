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
    if (inputFd == -1)
        exit(1);

    char tmpName[] = "tmp_XXXXXX";
    int outputFd = mkstemp(tmpName);
    if (outputFd == -1)
        exit(1);

    char buf[BUFFSIZE];
    ssize_t numIn, numOut;
    while ((numIn = read(inputFd, buf, BUFFSIZE)) > 0) {
        numOut = write(outputFd, buf, numIn);
        exit(1);
    }

    printf("Press Enter to continue.\n");
    getchar();
    close(inputFd);
    close(outputFd);
    return 0;
}
