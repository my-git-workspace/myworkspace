#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/signal.h>
#include <asm/siginfo.h>
#include <linux/sched.h>
#include "common.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Somnath");
MODULE_DESCRIPTION("signal_module device test module");

#define CDEV_NAME "mydev"
static void seng_signal(void){
	struct siginfo info;
        int ret=0;

        info.si_signo = MODULE_SIGNAL;
        info.si_code =  SI_QUEUE;
        info.si_int = MODULE_SIGNAL + 10000000; /* TODO*/
	//info.si_ptr = "ABC";
        ret = send_sig_info(MODULE_SIGNAL,&info,current);
        if(ret < 0)
        	printk(KERN_INFO "fail to send the signal info\n");
}

//ssize_t (*read) (struct file *, signal_module __user *, size_t, loff_t *);

static ssize_t signal_module_read(struct file* f, char __user *u, size_t size, loff_t *lt){
	printk(KERN_INFO "signal_module_read() called");
	return (ssize_t)0;
}
//ssize_t (*write) (struct file *, const signal_module __user *, size_t, loff_t *);

static ssize_t signal_module_write (struct file* f, const char __user *u, size_t size, loff_t *lt){
	printk(KERN_INFO "signal_module_write() called");
	return (ssize_t)0;
}


//int (*open) (struct inode *, struct file *);
int signal_module_open(struct inode *i, struct file *f){
	printk(KERN_INFO "signal_module_open called \n");
	return 0;
}
//int (*release) (struct inode *, struct file *);
int signal_module_release(struct inode *i, struct file *f){
	seng_signal();
	printk(KERN_INFO "signal_module_release called \n");
	return 0;
}


struct file_operations fops={
	.open=signal_module_open,
	.read=signal_module_read,
	.write=signal_module_write,
	.release=signal_module_release
};

static int major_number=0;
static int __init init_signal_module(void){
	major_number=register_chrdev(0, CDEV_NAME, &fops);
	printk(KERN_INFO "register_chrdev major: %d\n", major_number);
	return 0;
}

static void  __exit exit_signal_module(void){
	unregister_chrdev(major_number, CDEV_NAME);
	printk(KERN_INFO "unregister_chrdev %d\n", major_number);
}
module_init(init_signal_module);
module_exit(exit_signal_module);
