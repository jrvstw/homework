#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_special(void)
{
    int a = 30;
    return a;
}
