#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

#define BUF_SIZE 100

int main()
{
    int fd = open("grade", O_WRONLY | O_APPEND | O_CREAT, 0664);
    char buf[BUF_SIZE];
    char respond;
    while (1) {
        printf("Input an entry: ");
        fgets(buf, BUF_SIZE, stdin);

        if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
            fprintf(stderr, "File locked. Please wait.\n");
            flock(fd, LOCK_EX);
        }

        write(fd, buf, strlen(buf));
        printf("Entry accepted.\n");

        printf("Press enter to unlock...");
        do respond = fgetc(stdin);
        while (respond != '\n');

        flock(fd, LOCK_UN);
        printf("File unlocked.\n\n");
    }
    close(fd);
    return 0;
}
