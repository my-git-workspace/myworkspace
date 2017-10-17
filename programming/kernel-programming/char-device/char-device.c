#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Somnath");
MODULE_DESCRIPTION("char device test module");

#define CDEV_NAME "mydev"

//ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);

static ssize_t char_read(struct file* f, char __user *u, size_t size, loff_t *lt){
	printk(KERN_INFO "char_read() called");
	return (ssize_t)0;
}
//ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);

static ssize_t char_write (struct file* f, const char __user *u, size_t size, loff_t *lt){
	printk(KERN_INFO "char_write() called");
	return (ssize_t)0;
}


//int (*open) (struct inode *, struct file *);
int char_open(struct inode *i, struct file *f){
	printk(KERN_INFO "char_open called \n");
	return 0;
}
//int (*release) (struct inode *, struct file *);
int char_release(struct inode *i, struct file *f){
	printk(KERN_INFO "char_release called \n");
	return 0;
}



struct file_operations fops={
	.open=char_open,
	.read=char_read,
	.write=char_write,
	.release=char_release
};

static int major_number=0;
static int __init init_char_module(void){
	major_number=register_chrdev(0, CDEV_NAME, &fops);
	printk(KERN_INFO "register_chrdev major: %d\n", major_number);
	return 0;
}

static void  __exit exit_char_module(void){
	unregister_chrdev(major_number, CDEV_NAME);
	printk(KERN_INFO "unregister_chrdev %d\n", major_number);
}
module_init(init_char_module);
module_exit(exit_char_module);
