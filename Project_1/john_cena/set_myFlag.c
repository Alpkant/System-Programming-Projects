#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/capability.h>
#include <linux/printk.h>



asmlinkage int set_myFlag(pid_t pid, int flag){
	printk(KERN_INFO "set_myFlag pid:%d flag:%d\n",pid,flag);
	if(!capable(CAP_SYS_ADMIN))
		return -EPERM; /* Caller process does not have root privileges */

	if(flag != 0 && flag != 1)
		return -EINVAL; /* Flag is invalid */
	
	struct task_struct* target = find_task_by_vpid(pid);
	
	if(target == NULL)
		return -ESRCH; /* No such process is found */

	get_task_struct(target);
	printk(KERN_INFO "target before assignment flag:%d",target->myFlag);
	target->myFlag = flag;
	printk(KERN_INFO "target after assignment flag:%d",target->myFlag);
	put_task_struct(target);
	return 0;
}