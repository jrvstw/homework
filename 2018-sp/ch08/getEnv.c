#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i;
	char* value;
	for (i=1; argv[i]!=NULL; i++) {
		value = getenv(argv[i]);
		printf("%s=%s\n", argv[i], value);
	}
	
	return 0;
}

