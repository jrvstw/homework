#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

#define BUF_SIZE 30

int main()
{
    char buf[BUF_SIZE];
    char respond;
    int fd;
    fd = open("grade", O_WRONLY | O_APPEND | O_CREAT, 0664);
    while (1) {
        printf("\nInput an entry: ");
        fgets(buf, BUF_SIZE, stdin);

        flock(fd, LOCK_EX);
        printf("Confirm? (y/n)");

        do respond = fgetc(stdin);
        while (respond != 'y' && respond != 'n');
        getchar();

        if (respond == 'y') {
            write(fd, buf, strlen(buf));
            flock(fd, LOCK_UN);
            printf("Entry accepted. File unlocked.\n");
        } else {
            flock(fd, LOCK_UN);
        }
    }
    close(fd);
    return 0;
}
