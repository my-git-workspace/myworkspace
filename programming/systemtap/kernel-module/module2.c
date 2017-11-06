#include <linux/module.h>
extern void mod1fun(void);
static int __init my_init( void )
{
     printk("Hello world from module2\n");
      mod1fun();
       return 0;
}
static void __exit my_exit( void )
{
     printk("Goodbye world from module2\n");
}
module_init( my_init );
module_exit( my_exit );
MODULE_LICENSE("GPL"); 
