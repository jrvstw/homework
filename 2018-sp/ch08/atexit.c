#include <stdio.h>
#include <stdlib.h>


void myName() {
	printf("shiwulo\n");
}

int main(int argc, char **argv) {
	atexit(myName);
	return 0;
}

