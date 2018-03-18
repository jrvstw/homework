#include <assert.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int pipefd[2];
	char buf[200];
	
	int ret;
	pipe(pipefd);
	ret = fork();
	assert(ret>=0);
	if (ret==0) {	/*child*/
		close(1);
		dup(pipefd[1]);
		close(pipefd[1]);
		close(pipefd[0]);
		printf("hello");
	} else {
		close(0);
		dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		scanf("%s", buf);
		printf("parent: %s\n", buf);
	}
	return 0;
}

