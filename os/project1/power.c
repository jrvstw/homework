#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_power(long a, long b)
{
    int c = 1;
    while (b-- > 0)
        c *= a;
    return c;
}
