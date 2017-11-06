#include <linux/kernel.h>
#include <linux/module.h>

static void foo(void){
	printk("foo called\n");
}

MODULE_LICENSE("GPL");
static int __init init_hello_module(void){
	printk( KERN_INFO "init_hello_module \n");
	return 0;
}

static void  __exit exit_hello_module(void){
    	foo();
	printk(KERN_INFO "exit_hello_module \n");

}
module_init(init_hello_module);
module_exit(exit_hello_module);
