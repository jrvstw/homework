#include <stdio.h>
#define BUFFSIZE 4096

int main(int argc, char **argv)
{
    FILE *inputFile;
    inputFile = fopen(argv[1], "r");

    FILE *outputFile = tmpfile();

    char buf[BUFFSIZE];
    while (fread(buf, 1, BUFFSIZE, inputFile) > 0) {
        fprintf(outputFile, "%s", buf);
    }

    getchar();
    //fwrite(buf, 1, numIn, stdout);
    fclose(inputFile);
    return 0;
}
