#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
MODULE_LICENSE("GPL");

#define printf printk

struct test1 {
     int a;
};
struct test3{
	struct test1 *mt;
};
struct test2 {
     int b;
     struct test1 *z;
     int c;
};

int main(void)
{
     /* existing structure */
     struct test2 *obj;
      obj = (struct test2 *)vmalloc(sizeof(struct test2));
       if(obj == NULL){
	          printf("Error: Memory not allocated...!\n");
		   }
       obj->z = (struct test1 *)vmalloc(sizeof(struct test1));
       obj->z->a = 51;
       obj->b = 43;
       obj->c = 53;
	   
     struct test3 obj3;
     obj3.mt=(struct test1 *)vmalloc(sizeof(struct test1));
     obj3.mt->a=100;
     /* pointer to existing entry */    
#if 0
     struct test1 **obj1 = &(obj->z);
     struct test1 *objx = obj->z;
     //struct test2 *obj2 = container_of(&(objx), struct test2 , z); //wrong should give address of member from that struct
     struct test2 *obj2 = container_of(obj1, struct test2 , z);   //working
     //struct test2 *obj2 = container_of(&(obj->c), struct test2 , c); //working
     printf("obj2: %p obj2->b = %d\n", obj2,obj2->b);
     printf("obj: %p obj->b = %d\n", obj,obj->b);
#endif
     struct test2 *obj2 = container_of(&(obj3.mt), struct test2 , z);   //working
     printf("obj2: %p obj2->b = %d\n", obj2,obj2->b);
     printf("obj: %p obj->b = %d\n", obj,obj->b);
     vfree(obj->z);
     vfree(obj);
     return 0;

}
static int __init init_container_module(void){
	printk(KERN_INFO "init_container_module \n");
	return main();
}

static void  __exit exit_container_module(void){
	printk(KERN_INFO "exit_container_module \n");

}
module_init(init_container_module);
module_exit(exit_container_module);
