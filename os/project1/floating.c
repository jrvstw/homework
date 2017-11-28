#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage double sys_floating(void)
{
    double a = 2.718;
    return a;
}
