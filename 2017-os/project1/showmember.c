#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage int sys_showmember(void)
{
    printk("Team 23: 402125039, 404420020\n");
    return 0;
}
