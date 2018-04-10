#include <stdio.h>
#include <unistd.h>

int main()
{
    char buf[100];
    setvbuf(stdout, buf, _IOLBF, 100);
    printf("a");
    sleep(1);
    printf("b");
    sleep(1);
    printf("\n");
    return 0;
}

