#include<linux/kthread.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>

static struct task_struct *thread1,*thread2;
static int flag = 0;
#define UNLOCKED 0
#define LOCKED 1

static long lock = UNLOCKED;

void Acquire(int x) {
   while(lock == LOCKED);
   printk(KERN_INFO "\n");
      int p=1;
      p=p+x;
      printk(KERN_INFO "p->%d",p);
      printk(KERN_INFO "\n"); 
   lock = LOCKED;
}  /* Acquire */

void Relinquish(int x) {
   lock = UNLOCKED;
   printk(KERN_INFO "\n"); 
      int p=1;
      p=p*x;
      printk(KERN_INFO "p->%d",p);
      printk(KERN_INFO "\n");
   printk("\n");

	flag = 1;
}  /* Relinquish */


int work(void){
   long i;
   int l=2;

   for (i = 0; i < 5; i++) {
      Acquire(l);
      printk("\n");
      Relinquish(l);
      printk("\n");
   }
  return 0;
}  /* Thread_work */

asmlinkage long sys_spinlock(void)
{
   char our_thread[7]="thread1";
   thread1=kthread_create(work,NULL,our_thread);
   if ((thread1)) 
   {
     printk(KERN_INFO "in if");
     wake_up_process(thread1);
   }

	if( flag == 1)
  kthread_stop(thread1);
	return 0;
}

MODULE_LICENSE("GPL");
