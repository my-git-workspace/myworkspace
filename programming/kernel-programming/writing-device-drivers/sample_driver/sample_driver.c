#ifdef __KERNEL__
#include <linux/module.h>
#include <linux/fs.h>

dev_t first;
unsigned int count=0;
char *dev_name="mchardev";
int init_char_dev(void){
	int err=0;
	err=register_chrdev_region(first,count,dev_name);
	if(err){
	    return err;
	}
	printk(KERN_INFO "register_chrdev_region: success\n");
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
int main(int argc, char **argv[]){
	printf("This is userland\n");
	//return from main
	return (0);
}
#endif /* KERNEL */
