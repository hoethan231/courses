#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/uaccess.h>
//#include <asm/param.h>

#define BUFFER_SIZE 128
#define PROC_NAME "seconds"

static unsigned long START_TIME;

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct proc_ops proc_ops = {
	.proc_read = proc_read,
};

static int proc_init(void) {
	proc_create(PROC_NAME, 0666, NULL, &proc_ops);
	START_TIME = jiffies;
	return 0;
}

static void proc_exit(void) {
	remove_proc_entry(PROC_NAME, NULL);
}

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
	int rv = 0;
	char buffer[BUFFER_SIZE];

	if (*pos > 0) {
		return 0;
	}
	
	rv = sprintf(buffer, "Elapsed Seconds: %lu\n", (jiffies - START_TIME)/HZ);
	
	if(copy_to_user(usr_buf, buffer, rv)) {
		return -EFAULT;
	}
	*pos = rv;
	return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Programming Project 1: Seconds");
MODULE_AUTHOR("Ethan Ho");
