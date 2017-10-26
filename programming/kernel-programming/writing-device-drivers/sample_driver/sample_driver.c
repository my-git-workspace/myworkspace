#ifdef __KERNEL__
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
dev_t first;
unsigned int count=1;
char *dev_name="mchardev";
struct cdev *mycdev;
int cdev_open(struct inode *ip, struct file *fp){
	printk(KERN_INFO "%s\n",__func__);
    return 0;
}
int cdev_release(struct inode *ip, struct file *fp){
	printk(KERN_INFO "%s\n",__func__);
    return 0;
}
struct file_operations fops={
	open:cdev_open,
	release:cdev_release   
};
int init_char_dev(void){
	int err=0;
	err=alloc_chrdev_region(&first,MINOR(first),count,dev_name);
	printk(KERN_INFO "register_chrdev_region: success\n");

	mycdev=cdev_alloc();	
	cdev_init(mycdev,&fops);
	cdev_add(mycdev, first,count);

	printk(KERN_INFO "Major: %d\n",MAJOR(first));
	printk(KERN_INFO "Minor: %d\n",MINOR(first));
	return err;
}
static int init_sample_driver(void){
	printk(KERN_INFO "%s\n",__func__);
	if(init_char_dev()){
		printk(KERN_INFO "init_char_dev failed\n");
	}
	return (0);
}
int free_char_dev(void){
	int err=0;
	unregister_chrdev_region(first,count);
	cdev_del(mycdev);
	printk(KERN_INFO "unregister_chrdev_region: success\n");
	return err;
}
static void exit_sample_driver(void){
    	if(free_char_dev()){
		printk(KERN_INFO "free_char_dev failed\n");
	}
	printk(KERN_INFO "%s\n",__func__);
}
module_init(init_sample_driver);
module_exit(exit_sample_driver);
#else /* !KERNEL */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char **argv[]){
	printf("This is userland\n");
	int fd=open("/dev/mycdev",O_RDWR);
	if(fd==-1){
		printf("device opening failed\n");
		perror("open mycdev failed");
		return 0;
	}
	printf("/dev/mycdev open success\n");
	close(fd);
	//return from main
	return (0);
}
#endif /* KERNEL */
