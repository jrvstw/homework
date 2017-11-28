#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_add(long a, long b)
{
    int c = a + b;
    return c;
}
