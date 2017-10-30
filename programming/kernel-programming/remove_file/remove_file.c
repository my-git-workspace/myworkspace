#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/namei.h>
#include <linux/dcache.h>
#include <linux/fs.h>
//filepath="/mnt/sample.cache";
#define lpl_inode_lock_nested(ip, s)    mutex_lock_nested(&(ip)->i_mutex, s)
#define lpl_inode_unlock(ip)            mutex_unlock(&(ip)->i_mutex)
#if 0
static void
lpl_basename(const char *s, const char **str, int *len)
{
        size_t i, end;

        if (!s || !*s) {
                *str = ".";
                *len = 1;
                return;
        }

        i = strlen(s) - 1;

        while (i && s[i--] == '/');
    
        if (i == 0) {
                *str = "/";
                *len = 1;
                return;
        }

        end = i;
        
        for (end = i; i; i--) {
                if (s[i] == '/') {
                        *str = &s[i+1];
                        *len = end - i + 1;
                        return;
                }
        }

        *str = s;
        *len = end + 1;
}

int remove_file(const char *name){
	int rc=0;
	struct path parent;
	struct dentry *dentry;
	int len=0;
	const char *basename;
	rc=kern_path(name, LOOKUP_PARENT, &parent);
	if (rc){
	    printk("kern_path failed: rc : %d\n",rc);
	    return (ERR_PTR(rc));
	 }
	/* use I_MUTEX_PARENT because vfs_unlink needs it */
	//mutex_lock_nested((&(parent.dentry->d_inode))->i_mutex, I_MUTEX_PARENT);
	//lpl_inode_lock_nested(parent.dentry->d_inode, I_MUTEX_PARENT);
	lpl_basename(name,&basename,&len);
	mutex_lock(&parent.dentry->d_inode->i_mutex);
	dentry = lookup_one_len(basename, parent.dentry, len);
	mutex_unlock(&parent.dentry->d_inode->i_mutex);
	if (IS_ERR(dentry)) {
	    printk("lookup_one_len failed basename:%s len:%d\n",basename,len);
	    printk("dentry: %p\n",dentry);
	    printk("parent dentry d_iname: %s\n",(parent.dentry)->d_iname);
	    printk("IS_ERR(dentry): %d\n",IS_ERR(dentry));
	    printk("IS_ERR(parent.dentry): %d\n",IS_ERR(parent.dentry));
	}
	//lpl_inode_unlock(parent.dentry->d_inode);
	path_put(&parent);
	return 0;
}
#endif
static int ls_test( void )
{
  char *argv[] = { "/bin/bash", "-c", "/bin/ls >> /tmp/lsout-kern", NULL };
  static char *envp[] = {
      	"HOME=/",
	"TERM=linux",
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
 
  return call_usermodehelper( argv[0], argv, envp, UMH_WAIT_PROC );
}


static int remove_zpool_cache(void){
  char *name="/mnt/sample.cache";  
  char cmd_buf[32];
  sprintf(cmd_buf,"/bin/rm -f %s",name);
  char *argv[] = { "/bin/bash", "-c",cmd_buf, NULL };
  static char *envp[] = {
      	"HOME=/",
	"TERM=linux",
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
  	return call_usermodehelper( argv[0], argv, envp, UMH_WAIT_PROC);
}

void free_test(void){
    char *argv[4];
    char *envp[4];
    argv[0] = "/bin/bash";
    argv[1] = "-c";
    argv[2] = "/usr/bin/free >> /tmp/free-kern";
    argv[3] = NULL;

    envp[0] = "HOME=/";
    envp[1] = "TERM=linux";
    envp[2] = "PATH=/sbin:/usr/sbin:/bin:/usr/bin";
    envp[3] = NULL;

    printk( "free_test: %d\n",call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC));
}
static int init_remove_file(void){
	printk("======%s==========\n",__func__);	
	//int x=10;
	//printk("IS_ERR: %d\n", IS_ERR(&x));
	//printk("remove_file:%d\n",remove_file("/home/msys/myworkspace/programming/kernel-programming/remove_file/abc"));
	//printk("ls_test:%d\n",ls_test());
	printk("remove_zpool_cache:%d\n",remove_zpool_cache());
	//free_test();
    	return 0;
}
static void cleanup_remove_file(void){
	printk("======%s=========\n",__func__);	
}
module_init(init_remove_file);
module_exit(cleanup_remove_file);
