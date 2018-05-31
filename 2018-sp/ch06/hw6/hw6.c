#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

void myls(char *filename, int level)
{
    struct dirent **nameList;
    int nEntries = scandir(filename, &nameList, 0, alphasort);
    for (int n = 0; n <nEntries; n++) {
        for (int i = 0 ; i < level ; i++)
            printf("|   ");
        printf("%s\n", nameList[n]->d_name);
        if (nameList[n]->d_type == DT_DIR &&
            strcmp(nameList[n]->d_name, ".") != 0 &&
            strcmp(nameList[n]->d_name, "..") != 0) {
            char *tmpName = (char*)malloc(PATH_MAX);
            sprintf(tmpName, "%s/%s", filename, nameList[n]->d_name);
            myls(tmpName, level + 1);
        }
        free(nameList[n]);
	}
    free(nameList);
}

int main(int argc, char **argv)
{
	myls(argv[1], 0);
	return 0;
}

