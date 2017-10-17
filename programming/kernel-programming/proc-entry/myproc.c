/*
	This sample compiled on linux kernel 4.2.8
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include<linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

/*
	reference https://www.ibm.com/developerworks/library/l-proc/index.html
*/
int len,temp;

char *msg;
#define PROC_ENTRY "myproc"
#define PRINTK_INFO(x) printk(KERN_INFO x )
int open_proc(struct inode *ip, struct file *fp){
 	PRINTK_INFO("open_proc called\n");	
	return 0;
}

void current_threadinfo_wrapper(void){

    	int str_len=0;
	struct thread_info *cur_thread_info=current_thread_info();
 	printk( KERN_INFO "cur_thread_info->task->pid : %d \n", cur_thread_info->task->pid);	
 	printk( KERN_INFO "cur_thread_info->task->comm : %s \n", cur_thread_info->task->comm);	
	str_len=sizeof(cur_thread_info->task->pid)+strlen(cur_thread_info->task->comm);
	msg=vmalloc(str_len*sizeof(char));
	snprintf(msg, str_len, "cur_thread_info->task->pid : %d \n cur_thread_info->task->comm : %s \n", cur_thread_info->task->pid, cur_thread_info->task->comm);
}

void get_all_process(void){
    	struct task_struct *task;
	for_each_process(task) {
    		/* this pointlessly prints the name and PID of each task */
		printk("%s[%d]\n", task->comm, task->pid);
	}
}

ssize_t read_proc(struct file *fp,char __user *buf,size_t count,loff_t *offp ) 
{
 	PRINTK_INFO("read_proc called\n");	
	if(count>temp){
		count=temp;
	}
	temp=temp-count;
	//unsigned long copy_to_user (	void __user *  	to, const void * from, unsigned long  	n);
  	//current_threadinfo_wrapper(); 
	copy_to_user(buf,msg, count);
	//get_all_process();
	if(count==0)
		temp=len;
	return count;
}

ssize_t write_proc(struct file *fp,const char __user *buf,size_t count,loff_t *offp){
 	PRINTK_INFO("write_proc called\n");	
	//unsigned long copy_from_user (void * to, const void __user * from, unsigned long n);
	msg=vmalloc(count*sizeof(char));	
	copy_from_user(msg, buf,count);
	len=count;
	temp=len;
	return count;
}

struct file_operations proc_fops={
	.owner = THIS_MODULE,
	.open = open_proc,
	.read = read_proc,
	.write = write_proc
};

void create_new_proc_entry(void) {
	struct proc_dir_entry *proc_file_entry=proc_create(PROC_ENTRY,0666,NULL,&proc_fops);
	if(proc_file_entry == NULL)
 		PRINTK_INFO("proc_file_entry == NULL\n");	
}

int proc_init (void) {
	create_new_proc_entry();
	printk(KERN_INFO "proc_init called\n");
 	return 0;
}

void proc_cleanup(void) {
	printk(KERN_INFO "proc_cleanup called\n");
	vfree(msg);	
 	remove_proc_entry(PROC_ENTRY,NULL);
}

MODULE_LICENSE("GPL"); 
module_init(proc_init);
module_exit(proc_cleanup);

