#include <stdlib.h>
#include <stdio.h>
extern char **environ;

int main(int argc, char**argv) {
	int i;
	while(environ[i] != NULL) {
		printf("%s\n", environ[i++]);
	}
}
