#include <linux/module.h>
static int __init my_init( void )
{
     printk("Hello world from module 1 \n");
      return 0;
}
static void __exit my_exit( void )
{
     printk("Goodbye world from module 1 \n");
}
static void mod1fun(void)
{
     printk("YAHOO ! I got into mod1fun \n");
}
EXPORT_SYMBOL(mod1fun);
module_init( my_init );
module_exit(my_exit);
MODULE_LICENSE("GPL");
