#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("%ld\n%ld\n%ld\n",
           syscall(341,5,10),
           syscall(342,5,10),
           syscall(343,3,6));
    syscall(344);
    printf("%ld\n%f\n%ld\n",
           syscall(345),
           syscall(346),
           syscall(347));
    return 0;
}

