#ifdef __KERNEL__
#include <linux/module.h>
#include <linux/fs.h>

static int init_sample_driver(void){
	printk(KERN_INFO "%s\n",__func__);
	return (0);
}
static void exit_sample_driver(void){
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
#endif
