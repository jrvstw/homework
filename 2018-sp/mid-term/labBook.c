#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <assert.h>
#include <dirent.h>

#define SUPERVISOR pc341
#define BUF_SIZE 4096

int name2id(char username[])
{
    struct passwd *user;
    user = getpwnam(username);
    assert(user != NULL);
    return user->pw_uid;
}

void writeFile(char *argv, char *outputDir)
{
    int inputFd,
        outputFd;
    ssize_t numIn,
            numOut;
    char buf[BUF_SIZE];
    off_t begin = 0,
          end = 0;
    int fileSize,
        blockSize,
        pos = 0;

    inputFd = open(argv, O_RDONLY);
    outputFd = open(outputDir, O_WRONLY | O_CREAT, 0640);
    chown(outputDir, name2id("pc341"), getpwuid(getuid())->pw_uid);
    ftruncate(outputFd, 0);

    fileSize = lseek(inputFd, 0, SEEK_END);
    lseek(inputFd, 0, SEEK_SET);

    while (1) {
		pos = lseek(inputFd, pos, SEEK_DATA);
		begin = pos;
		pos = lseek(inputFd, pos, SEEK_HOLE);
		end = pos;
		blockSize=end-begin;
		lseek(inputFd, begin, SEEK_SET);
		lseek(outputFd, begin, SEEK_SET);
        while ((numIn = read(inputFd, buf, BUF_SIZE)) > 0) {
            numOut = write(outputFd, buf, (ssize_t)numIn);
			if (numIn != numOut) perror("numIn != numOut");
			blockSize-=numIn;
			if (blockSize == 0) break;
        }
		if (lseek(outputFd, 0, SEEK_CUR) == fileSize) break;
    }

    close(inputFd);
    close(outputFd);
}

void writeAny(char *argv, char *outputDir)
{
    int fd;
    DIR *dir;
    struct dirent *ent;
    if (fd = open(argv, O_RDONLY)) {
        writeFile(argv, outputDir);
        close(fd);
    } else if (dir = opendir(argv)) {
        char newDir[150];
        strcat(newDir, outputDir);
        strcat(newDir, argv);
        mkdir(newDir, 0750); 
        chown(newDir, name2id("pc341"), getpwuid(getuid())->pw_uid);
        strcat(newDir, "/");
        ent = readdir(dir);
        while (ent != NULL) {
            ent = readdir(dir);
        }
        closedir(dir);
    }
    return;
}

int main(int argc, char **argv)
{
    char outputDir[100] = "/home/labBook/",
         userName[10] = "jwye",
         timeStamp[30];

    strcat(outputDir, userName);
    mkdir(outputDir, 0750); 
    chown(outputDir, name2id("pc341"), getpwuid(getuid())->pw_uid);
    strcat(outputDir, "/");

    time_t t = time(NULL);
    struct tm *pTM = localtime(&t);   
    int yyyy = pTM->tm_year + 1900;
    int mm = pTM->tm_mon + 1;
    int dd = pTM->tm_mday;
    int hh = pTM->tm_hour;
    int min = pTM->tm_min;
    int ss = pTM->tm_sec;
    sprintf(timeStamp, "%04d-%02d-%02d-%02d:%02d:%02d", yyyy, mm, dd, hh, min, ss);
    strcat(outputDir, timeStamp);
    mkdir(outputDir, 0750); 
    chown(outputDir, name2id("pc341"), getpwuid(getuid())->pw_uid);
    strcat(outputDir, "/");
    strcat(outputDir, argv[2]);

    writeFile(argv[1], outputDir);

    return 0;
}
