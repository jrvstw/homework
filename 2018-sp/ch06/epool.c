#define MAX_EVENTS 5
#define READ_SIZE 10
#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int running = 1, event_count, i;
    size_t bytes_read;
    char read_buffer[READ_SIZE + 1];
    struct epoll_event event, events[MAX_EVENTS];
	int fd;
    int epoll_fd = epoll_create1(0);
    assert(fd != -1);

	//for (i=1; i<argc; i++) {
		//fd=open(argv[i], O_RDONLY|O_CREAT, 666);
		event.events = EPOLLIN;
    	event.data.fd = 0;
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event) == -1) {
			perror(argv[i]);
		}
	//}

    while (running) {
		printf("\nPolling for input...\n");
		event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
		printf("%d ready events\n", event_count);
		for (i = 0; i < event_count; i++) {
	    	printf("Reading file descriptor '%d' -- ", events[i].data.fd);
	    	bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
	    	printf("%zd bytes read.\n", bytes_read);
	    	read_buffer[bytes_read] = '\0';
	    	printf("Read '%s'\n", read_buffer);
		}
    }
    close(epoll_fd);
}
