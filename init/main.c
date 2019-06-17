#include "vstring.h"
#include "m.h"
#include "types.h"
#include "processor.h"
#include "console.h"
extern void trap_init(void);
static struct task_struct init_task = INIT_TASK;
struct task_struct * task[10]={0};
extern void start_thread( void(*fun)());
extern struct mem_page* free_mem_page;
void syscall(uint a){
    asm(" int $0x80 \t\n"
            ::"a"(a):);
}
void delay(){
    for(int i = 0;i < 10000000;)
       i++; 
}
void init(){
    while(1){
        delay();
        printk("B");
    }
}
void three(){
    while(1){
        delay();
        printk("A");
    }
}
void two(){
    while(1){
        delay();
        printk("C");
    }
}
void one(){
    while(1){
        delay();
        printk("D");
    }
}



void mmain()
{
    uint mem = get_free_page() + 4096;
    printk("This in mmain() Mem is %dM \n", mem / (1024 * 1024));
    trap_init();
    mmemcpy(current,&init_task, sizeof(struct task_struct));
    for (int i = 0; i< 10;i++)
        task[i] = 0;
    //task[0] = current;
    //start_thread(init);
    //start_thread(three);
    //start_thread(two);
    //start_thread(one);
    char* ret = (char*)kmalloc(68);
    mmemcpy(ret,"aaaa",4);
    printk("%x \n",ret);
    char* ret1 = kmalloc(38);
    mmemcpy(ret,"aaaaa",5);
    printk("%x \n",ret);
    ret = (char*)kmalloc(99);
    //print_mem_page(free_mem_page);
    mmemcpy(ret,"good man",8);
    clear();
    print_mem(free_mem_page,50);
    kfree(ret1);
    print_mem(free_mem_page,50);
    char * p = kmalloc(20);
    print_mem(free_mem_page,50);
    kfree(p);
    print_mem(free_mem_page,50);
    while(1){
        asm("hlt\t\n");
    }
}
