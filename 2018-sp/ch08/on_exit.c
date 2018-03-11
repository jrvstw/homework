#include <stdio.h>
#include <stdlib.h>


void myName(int ret, void *arg) {
	printf("%s shiwulo\n", (char*)arg);
}

int main(int argc, char **argv) {
	char* p = "professor";
	on_exit(myName, p);
	return 0;
}

