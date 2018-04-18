#include <chr_dev.h>
#include <linux/fs.h>
#define DEVICE_NAME "chr_device"
int irq=12;
module_param(irq, int, 0);
//int (*open) (struct inode *, struct file *);
int open_chr_dev(struct inode *ip, struct file *fp){
	printk("%s called\n",__func__);
	return 0;
}
//int (*release) (struct inode *, struct file *);
int release_chr_dev (struct inode *ip, struct file *fp){
	printk("%s called\n",__func__);
	return 0;
}
//ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
ssize_t read_chr_dev(struct file *fp, char __user *ptr, size_t size, loff_t *off){
	printk("%s called\n",__func__);
	return (ssize_t)0;
}
//ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
ssize_t write_chr_dev (struct file *fp, const char __user *ptr, size_t size, loff_t *off){
	printk("%s called\n",__func__);
	return (ssize_t)0;
}
//long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
long unlocked_ioctl_chr_dev(struct file *fp, unsigned int request, unsigned long address){
	printk("%s called\n",__func__);
	printk("request: %d\n",request);
	return 0;
}
struct file_operations fops={
	open:open_chr_dev,
	read:read_chr_dev,
	write:write_chr_dev,
	unlocked_ioctl:unlocked_ioctl_chr_dev,
	release:release_chr_dev
};
int major=0;
void chr_dev_init(void){
	printk("%s called\n",__func__);
	//register_chrdev(unsigned int major, const char *name,const struct file_operations *fops);
	major=register_chrdev(0, DEVICE_NAME,&fops);
	//printk("irq: %d\n",irq);
	printk("chr_dev major: %d\n",major);
}

void chr_dev_exit(){
    	//static inline void unregister_chrdev(unsigned int major, const char *name);
    	unregister_chrdev(major, DEVICE_NAME);
	printk("%s called\n",__func__);
}
