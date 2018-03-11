#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
	int niceVal;
	int newNiceVal;
	int i;
	int ret=0;
	sscanf(argv[1], "%d", &niceVal);
	errno =0;
	newNiceVal = nice(niceVal);
	if (newNiceVal == -1 && errno !=0)
		perror("Error: nice");
	else {
		printf("new val = %d\n", newNiceVal);
	}

	for (int i=0; i<=5000000000; i++)
		ret+=i;
	return ret;
}

