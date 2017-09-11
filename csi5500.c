#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/init.h>

#include "csi5500.h"

asmlinkage long sys_csi5500(void) {

	struct list_head *child_tasks;

	printk("CSI5500 - Assignment 1\n");
	printk("Process: %s\n", current->comm);
	printk("Process ID: %ld\n", (long)task_pid_nr(current));
	printk("Process State: %ld\n", current->state);
	printk("Process Start Time: %lld\n", current->start_time);	
	printk("Parent Process: %s\n", current->parent->comm);
	printk("Parent Process ID: %ld\n", (long)task_pid_nr(current->parent));
	list_for_each(child_tasks, &current->parent->children) {
		struct task_struct *child_task;
		child_task = list_entry(child_tasks, struct task_struct, sibling);
		printk("	Sibling Process: %s\n", child_task->comm);
		printk("	Sibling Process ID: %ld\n", (long)task_pid_nr(child_task));
	}
	printk("Real Time: %lld\n", current->real_start_time);
	return 0;
}
