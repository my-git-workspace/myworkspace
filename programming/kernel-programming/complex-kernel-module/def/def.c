#include <header.h>
int print_data(){
	printk(KERN_INFO "%s %d\n", __FILE__, __LINE__);
	return 0;
}

