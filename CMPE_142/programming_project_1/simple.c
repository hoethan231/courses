#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_AUTHOR("Ethan Ho");
MODULE_DESCRIPTION("Simple module for OS programming project");
MODULE_LICENSE("GPL");


static int simple_init(void) {
    
    return 0;
}

static void simple_exit(void) {
    printk(KERN_INFO "Removing Kernel Module\n");
}

module_init(simple_init);
module_init(simple_exit);
