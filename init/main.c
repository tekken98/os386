#include "vstring.h"
#include "m.h"
#include "types.h"
#include "processor.h"
extern void trap_init(void);
static struct task_struct init_task = INIT_TASK;
struct task_struct * task[10]={0};
extern void start_thread( void(*fun)());
void syscall(uint a){
    asm(" int $0x80 \t\n"
            ::"a"(a):);
}
void init(){
    while(1)
        printk("B");
}
void three(){
    while(1)
        printk("A");
}
void two(){
    while(1)
        printk("C");
}
void one(){
    while(1)
        printk("D");
}



void mmain()
{
    uint mem = get_free_page() + 4096;
    printk("This in mmain() Mem is %dM \n", mem / (1024 * 1024));
    trap_init();
    mmemcpy(current,&init_task, sizeof(struct task_struct));
    for (int i = 0; i< 10;i++)
        task[i] = 0;
    task[0] = current;
    start_thread(init);
    start_thread(three);
    start_thread(two);
    start_thread(one);
    while(1){
        printk("god\n");
        asm("hlt\t\n");
        printk("hlt over\n");
    }
}
