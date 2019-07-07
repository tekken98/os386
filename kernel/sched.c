#include "sched.h"
#include "processor.h"
#include "vstring.h"
extern struct task_struct * task[];
struct thread_info {
    uint eip;
    uint cs;
    uint eflags;
    uint esp;
    uint ss;
};
const uint TASK_SIZE = 4096;
#define  THREAD_SIZE  sizeof(struct thread_info)
//#define THREAD_INFO(p) ((struct thread_info * )((uint)p + TASK_SIZE - THREAD_SIZE))
#define THREAD_INFO(p) (struct thread_info * )((uint)p + TASK_SIZE) - 1 
#define EFLAGS(p) asm("pushf\t\n"\
        "mov (%%esp),%0\t\n"\
        "popf \t\n"\
        :"=a"(p)::)
uint mfork(){
    alloc_task_struct(p);
    cch *g = "child";
    //memcpy(p,current,4096);
    mmemcpy((void*)p->name,(void*)g,6);
    task[1] = p;
    return (uint)p;
}
uint get_free_process(){
    for (int i = 0;i < 10;i++){
        if (task[i] == 0)
            return i;
    }
    return 0;
}
void start_thread( void (* fun)()){
    alloc_task_struct(p);
    mmemcpy(p,current,4096);
    struct thread_info * thread = THREAD_INFO(p);
    thread->eip = (uint)fun;
    thread->cs = 0x8;
    thread->eflags=0;
    thread->esp = (uint)thread;
    thread->cs = 0x18;
    uint e ;
    EFLAGS(e);
    thread->eflags=e;
    uint pid = get_free_process();
    p->esp = thread->esp;
    p->state=TASK_RUNNING;
    p->times=0;
    p->pid = pid;
    task[pid] = p;
}
void switch_to(struct task_struct * from, struct task_struct * to){
    if (from == to )
        return;
    asm(" pushf \t\n"
            "push %%ebp \t\n"
            "push $1f\t\n"
            "mov %%esp,(%%eax)\t\n"
            "mov (%%edx),%%esp \t\n"
            "ret \t\n"
            "1: \t\n"
            "pop %%ebp \t\n"
            "popf \t\n" 
            ::"a"(&(from->esp)),"d"(&(to->esp)):);

}

void schedule(){
    struct task_struct *from = current;
    struct task_struct *to;
    uint time = from->times++;
    uint min=0;
    for (int i = 1;i < 10; i++){
            //to = *(&task+i); // task[i] need  *task[]; declare
            to = task[i]; // task[i] need  *task[]; declare
            if (to && to->state == TASK_RUNNING){
                if (to->times < time)
                    min = i;
            }
    }
    if (min < 10){
        to = task[min];
        if (to)
            switch_to(from,to);
        //printk("times %d\n",from->times);
    }
}
void sleep_on(struct task_struct ** p){
    struct task_struct * tmp = *p;
    *p = current;
    (*p)->state = TASK_UNINTERRUPTIBLE;
    schedule();
    if (tmp){
        tmp->state =  TASK_RUNNING;
    }
}
void wake_up(struct task_struct **p){
    if (p && *p) {
        (*p)->state = TASK_RUNNING;
        *p = NULL;
    }
}
void exit(int err){
    current->state = TASK_ZOMBIE;
    task[current->pid] = NULL;
    free_page((ulong)current);
    schedule();
    printk("should never return here!");
}
