#include <stdio.h>
#include <stdlib.h>
#define BUFFSIZE 4096

int main(int argc, char **argv)
{
    FILE *inputFile = fopen(argv[1], "r");

    char tmpName[] = "tmp_XXXXXX";
    int fd = mkstemp(tmpName);
    FILE *outputFile = fdopen(fd, "w");

    char buf[BUFFSIZE];
    while (fread(buf, 1, BUFFSIZE, inputFile) > 0) {
        fprintf(outputFile, "%s", buf);
    }

    getchar();
    //fwrite(buf, 1, numIn, stdout);
    fclose(inputFile);
    return 0;
}
