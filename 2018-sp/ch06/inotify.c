#include <sys/inotify.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

void printInotifyEvent(struct inotify_event* event);

char wd[1000][10000];

int main(int argc, char **argv) {
	int fd;
	int num;
	char* p;
	char buf[BUF_LEN];
	int ret;
	int i;
	
	fd = inotify_init();
	assert(fd>0);
	for (i=1; i< argc; i++) {
		ret=inotify_add_watch(fd, argv[i], IN_ALL_EVENTS);
		assert(ret>0);
		strcpy(&(wd[i][0]), argv[i]);
	}
	while(1) {
		num = read(fd, buf, BUF_LEN);
		assert(num>0);
		for (p = buf; p < buf + num; ) {
			printInotifyEvent((struct inotify_event *) p);
			p+=sizeof(struct inotify_event) + ((struct inotify_event *)p)->len;
		}
	}
}

void printInotifyEvent(struct inotify_event* event) {
	printf("[%s] ", wd[event->wd]);
	printf("{");
	if (event->mask & IN_ACCESS) 		printf("IN_ACCESS, ");
	if (event->mask & IN_ATTRIB) 		printf("IN_ATTRIB, ");
	if (event->mask & IN_CLOSE_WRITE) 	printf("IN_CLOSE_WRITE, ");
	if (event->mask & IN_CLOSE_NOWRITE) 	printf("IN_CLOSE_NOWRITE, ");
	if (event->mask & IN_CREATE) 		printf("IN_CREATE, ");
	if (event->mask & IN_DELETE) 		printf("IN_DELETE, ");
	if (event->mask & IN_DELETE_SELF) 	printf("IN_DELETE_SELF, ");
	if (event->mask & IN_MODIFY) 		printf("IN_MODIFY, ");
	if (event->mask & IN_MOVE_SELF)		printf("IN_MOVE_SELF, ");
	if (event->mask & IN_MOVED_FROM)	printf("IN_MOVED_FROM, ");
	if (event->mask & IN_MOVED_TO)		printf("IN_MOVED_TO, ");
	if (event->mask & IN_OPEN)			printf("IN_OPEN, ");
	if (event->mask & IN_IGNORED)		printf("IN_IGNORED, ");
	if (event->mask & IN_ISDIR)			printf("IN_ISDIR, ");
	if (event->mask & IN_Q_OVERFLOW)	printf("IN_Q_OVERFLOW, ");
	printf("}");
	printf("cookie=%d", event->cookie);
	if (event->len>0)
    	printf(" name = %s\n", event->name);
	else
		printf(" name = null\n");
}
