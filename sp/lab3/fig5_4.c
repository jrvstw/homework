#include "apue.h"

int main(void)
{

	int c;
	int counter = 0;
	while( (c = getc(stdin)) != EOF ) {
        counter++;
        if(putc(c,stdout) == EOF)
            err_sys("output error");
    }

	if(ferror(stdin))
		err_sys("input error");
    printf("counter: %d\n", counter);
	exit(0);
}

