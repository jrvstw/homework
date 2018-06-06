#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_negative(void)
{
    int a = -2;
    return a;
}
