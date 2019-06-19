#include "vstring.h"
#include "m.h"
#include "types.h"
#include "processor.h"
#include "console.h"
#include "pci.h"
extern void trap_init(void);
//static struct task_struct init_task = INIT_TASK;
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
   //printk("fuck \n");
   /*
    mmemcpy(current,&init_task, sizeof(struct task_struct));
   for (int i = 0; i< 10;i++)
        task[i] = 0;
    task[0] = current;
    start_thread(init);
    start_thread(three);
    start_thread(two);
    start_thread(one);
    */
   /*
   for (int i = 0;i < 0x1000;i++)
       (*(char*)i) = 0xff;
   outb(0x1,0xcfb);
   outl(0x80000000,0xcf8);
   u32 ret = inl(0xcf8);
   */
   clear();
   for (int i = 0;i < 5;i += 1){
       for (int j = 0;j<32;j++){
           for(int k=0;k<8;k++){
               //u32 addr = 0x80000000 + i * 0x10000 + (j*8) * 0x100 + k * 0x100;
               u32 addr = pci_addr(i,j,k,PCI_CLASS_DEVICE);
               //asm("mov %1,%%edx;out %0,%%dx"::"a"(addr),"b"(0xcf8):"dx");
               outl(addr,0xcf8);
               //*((u32*)0xcf8) = addr;
               u16 ret = inw(0xcfc);
               //u32 ret = *((u32*)0xcfc);
               //int ret;
               //asm("mov %0,%%edx;inl %%dx":"=r"(ret):"0"(0xcfc):"dx");
               if (ret != 0xffff)
               {
                   printk(" bus:%02d,slot:%02d, %04x\n",i,j,ret);
               }
           }
       }
   }
   while(1){
        asm("hlt\t\n");
    }
}
