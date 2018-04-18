#include <chr_dev.h>

MODULE_AUTHOR("A LEARNER");
MODULE_LICENSE("GPL v2");

static int init_mod(void){
	printk("init_mod() routine called.\n");	
	chr_dev_init();
    	return (0);
}
void exit_mod(void){
	chr_dev_exit();
	printk("exit_mod() routine called.\n");
}
module_init(init_mod);
module_exit(exit_mod);
