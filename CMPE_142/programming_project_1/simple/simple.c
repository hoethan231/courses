#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CMPE_142 Programming Project 1: Simple Module");
MODULE_AUTHOR("Ethan Ho");

static int simple_init(void) {

	printk(KERN_INFO "Loading Kernel Module\n");	
	printk(KERN_INFO "The Golden Ratio is: %lu\n", GOLDEN_RATIO_PRIME);
	printk(KERN_INFO "HZ: %lu Jiffies: %lu\n", HZ, jiffies);
	return 0;

}

static void simple_exit(void) {
	printk(KERN_INFO "Removing Kernel Module\n");
	printk(KERN_INFO "The GCD of 3,300 and 24 is: %lu\n", gcd(3300, 24));
	printk(KERN_INFO "Jiffies: %lu\n", jiffies);
}

module_init(simple_init);
module_exit(simple_exit);
