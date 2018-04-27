#include <chr_dev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#define DEVICE_NAME "chr_device"
int irq=12;
int nr_open=0;
module_param(irq, int, 0);
typedef struct traveller{
	int index;
}traveller;
#define ram_disc_size (size_t) (64*PAGE_SIZE)
char ram_disc[ram_disc_size]={0};
//int (*open) (struct inode *, struct file *);
int open_chr_dev(struct inode *ip, struct file *fp){
	traveller *t=NULL;
	printk("%s called\n",__func__);
	nr_open++;
	printk("device opened %d times.\n",nr_open);
	t=kmalloc(sizeof(traveller),GFP_KERNEL);
	if(!ip->i_private){
		printk("allocation failed\n");
	}
	ip->i_private=t;
	t->index=1000;
	printk("ip->i_private: %p index: %d\n",ip->i_private,t->index);
	return 0;
}
//int (*release) (struct inode *, struct file *);
int release_chr_dev (struct inode *ip, struct file *fp){
	traveller *t=NULL;
	printk("%s called\n",__func__);
	t=ip->i_private;
	printk("ip->i_private: %p index: %d\n",ip->i_private,t->index);
	kfree(ip->i_private);
	return 0;
}
//ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
ssize_t read_chr_dev(struct file *fp, char __user *ptr, size_t size, loff_t *off){
	int nbytes=0;
	printk("%s called\n",__func__);
	printk("size: %d off: %d\n",(int)size, (int)*off);
	printk("ram_disc_size: %lu\n",ram_disc_size);
	if((size + *off) > ram_disc_size)
		return 0;	
	
	nbytes= size - copy_to_user(ptr, ram_disc+*off, size);
	printk("read: ram_disc:%s\n",ram_disc+*off);
	printk("nbytes: %d\n",nbytes);
	*off+=nbytes;
	return nbytes;
}
//ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
ssize_t write_chr_dev (struct file *fp, const char __user *ptr, size_t size, loff_t *off){
	int nbytes=0;
	printk("%s called\n",__func__);
	printk("size: %d off: %d\n",(int)size, (int)*off);
	if((size + *off) > ram_disc_size)
		return 0;	
	nbytes=size - copy_from_user(ram_disc+*off, ptr,size);
	printk("nbytes: %d\n",nbytes);
	printk("write: ram_disc:%s\n",ram_disc+*off);
	*off+=nbytes;
	return nbytes;
}
//long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
long unlocked_ioctl_chr_dev(struct file *fp, unsigned int request, unsigned long address){
	printk("%s called\n",__func__);
	printk("request: %d\n",request);
	return 0;
}
//loff_t (*llseek) (struct file *, loff_t, int);
loff_t llseek_chr_dev(struct file *fp, loff_t off, int whence){
	printk("%s called\n",__func__);
	switch(whence){
		case SEEK_SET:
		    	printk("SEEK_SET called\n");
			fp->f_pos+=off;
		    	break;
		case SEEK_CUR:
		    	printk("SEEK_CUR called\n");
			fp->f_pos+=off;
			break;
		case SEEK_END:
		    	printk("SEEK_END called\n");
			fp->f_pos+=ram_disc_size+off;
			break;
	
	}
	//fp->f_pos=fp->f_pos>ram_disc_size?ram_disc_size:fp->f_pos;
	//fp->f_pos=fp->f_pos>0?fp->f_pos: 0;
	return fp->f_pos;
}
struct file_operations fops={
	open:open_chr_dev,
	read:read_chr_dev,
	write:write_chr_dev,
	llseek:llseek_chr_dev,
	unlocked_ioctl:unlocked_ioctl_chr_dev,
	release:release_chr_dev
};
int major=0;
void chr_dev_init(void){
	printk("%s called\n",__func__);
	//register_chrdev(unsigned int major, const char *name,const struct file_operations *fops);
	major=register_chrdev(0, DEVICE_NAME,&fops);
	//printk("irq: %d\n",irq);
	printk("chr_dev major: %d\n",major);
}

void chr_dev_exit(){
    	//static inline void unregister_chrdev(unsigned int major, const char *name);
    	unregister_chrdev(major, DEVICE_NAME);
	printk("device opened %d times.\n",nr_open);
	printk("%s called\n",__func__);
}
