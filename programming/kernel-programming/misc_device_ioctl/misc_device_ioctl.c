#include <linux/module.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <linux/capability.h>
#include <asm/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>

struct test_ioctl {
        int cmd_no;
        char data[64];
};

#define SAMPLE_IOCTL_MAGIC_NUMBER 's'

#define SAMPLE_IOCTL_CMD_1 \
        _IOR(SAMPLE_IOCTL_MAGIC_NUMBER, 0x1, int)

#define SAMPLE_IOCTL_CMD_2 \
        _IOW(SAMPLE_IOCTL_MAGIC_NUMBER, 0x2, int)

#define SAMPLE_IOCTL_CMD_3 \
        _IO(SAMPLE_IOCTL_MAGIC_NUMBER, 0x3)

#define SAMPLE_IOCTL_CMD_4 \
        _IOWR(SAMPLE_IOCTL_MAGIC_NUMBER, 0x4, struct test_ioctl)

static ssize_t sample_char_read(struct file * file, char __user * buf,
                       size_t count, loff_t *ppos)
{
       printk("sample_char_read size(%ld)\n", count);
       return 0;
}

static ssize_t sample_char_write(struct file *filp, const char *buf,
                 size_t size, loff_t *offp)
{
       printk("sample_char_write size(%ld)\n", size);
       return size;

}

int sample_char_open(struct inode *inode, struct file *filp)
{
       printk("sample_char_open\n");
       return 0;
}

int sample_char_release(struct inode *inode, struct file *filp)
{

       printk("sample_char_release\n");
       return 0;
}

int sample_char_ioctl (struct file *filp,unsigned int cmd, unsigned long arg)
{
 int ret = 0;

 printk("sample_char_ioctl\n");

 switch (cmd) {

 case SAMPLE_IOCTL_CMD_1:
  printk("IOCTL CMD1\n");
  /*Do Something*/
  break;
 case SAMPLE_IOCTL_CMD_2:
  printk("IOCTL CMD2\n");
  /*Do Something*/
  break;
 case SAMPLE_IOCTL_CMD_3:
  printk("IOCTL CMD3\n");
  /*Do Something*/
  break;
 case SAMPLE_IOCTL_CMD_4:
  printk("IOCTL CMD4\n");
  /*Do Something*/
  break;

 default: /*Default option*/
  /*Do Something or return invalid command error*/
  printk("Invalid IOCTL CMD\n");
  ret = -EINVAL;
 }
 return ret;
}

static struct file_operations sample_char_fops = {
       read:          sample_char_read,
       write:          sample_char_write,
       open:          sample_char_open,
       release:        sample_char_release,
 unlocked_ioctl: sample_char_ioctl,
};

static struct miscdevice misc_dev = {
 .minor =  MISC_DYNAMIC_MINOR,
        .name = "sample_misc_dev",
        .fops =  &sample_char_fops,
        .mode = S_IRWXUGO,
};

int init_module(void)
{
 int ret = 0;
 printk("\nLoading the sample misc char device driver\n");
 ret = misc_register(&misc_dev);
 if (ret)
  printk("Unable to register misc dev\n");
 return ret;
}

void cleanup_module(void)
{
        printk("\nUnloading the sample char device driver\n");
 misc_deregister(&misc_dev);

}
