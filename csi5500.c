#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/time.h>

#include "csi5500.h"

asmlinkage long sys_csi5500(void) {
	
	/*list_head pointer to retrieve child tasks*/
	struct list_head *child_tasks;
	/*timeval instance to process get time of day*/
	struct timeval tv;
	/*tm struct instance to access tm members that contain hours, minutes and seconds*/
	struct tm curr_time;

	printk("CSI5500 - Assignment 1\n");
	/*current process name*/
	printk("Process: %s\n", current->comm);
	/*current process id*/
	printk("Process ID: %ld\n", (long)task_pid_nr(current));
	/*process state will be zero - which is the equivalent of 'Running'*/
	if (current->state == 0) {
		printk("Process State: %ld - Running\n", current->state);
	}
	/*convert from nanoseconds to seconds*/
	printk("Process Start Time: %lld seconds (roughly)\n", current->start_time / 1000000000);
	/*use timeval struct to retrieve time of day*/
	do_gettimeofday(&tv);
	/*convert to tm struct type*/
	time_to_tm(tv.tv_sec, 0, &curr_time);
	/*construct timestamp from tm struct members - results will be based off UNIX UTC and EPOCH standard*/
	printk("Process Time Stamp: %d:%d:%d UTC (Converted from EPOCH)\n",
			curr_time.tm_hour,
			curr_time.tm_min,
			curr_time.tm_sec);
	/*current process parent name*/	
	printk("Parent Process: %s\n", current->parent->comm);
	/*current process parent id*/
	printk("Parent Process ID: %ld\n", (long)task_pid_nr(current->parent));
	/*create list for all child tasks in the current process pointer*/
	list_for_each(child_tasks, &current->parent->children) {
		/*use new task_struct for each child task*/
		struct task_struct *child_task;
		child_task = list_entry(child_tasks, struct task_struct, sibling);
		printk("	Sibling Process: %s\n", child_task->comm);
		printk("	Sibling Process ID: %ld\n", (long)task_pid_nr(child_task));
	}
	printk("Complete.\n");
	return 0;
}
