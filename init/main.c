#include "vstring.h"
#include "m.h"
#include "types.h"
#include "processor.h"
#include "console.h"
#include "pci.h"
#include "ide.h"
#include "io.h"
extern void trap_init(void);
//static struct task_struct init_task = INIT_TASK;
struct task_struct * task[10]={0};
extern void start_thread( void(*fun)());
extern struct mem_page* free_mem_page;
extern void (*do_hd)();
extern void reset_hd();
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
        delay();
        printk("this is from hd_interrupt");
}
void pci_base_addr(int bus,int dev, int fuc){
    u32 ret;
    int i = bus;
    int j = dev;
    int k = fuc;
    ret = read_pci_config(i,j,k,PCI_BASE_ADDRESS_0);
    printk("%08x ",ret);
    ret = read_pci_config(i,j,k,PCI_BASE_ADDRESS_1);
    printk("%08x ",ret);
    //printk("%08x ",ret);
    ret = read_pci_config(i,j,k,PCI_BASE_ADDRESS_2);
    printk("%08x ",ret);
    //printk("%08x ",ret);
    ret = read_pci_config(i,j,k,PCI_BASE_ADDRESS_3);
    printk("%08x ",ret);
    //printk("%08x ",ret);
    ret = read_pci_config(i,j,k,PCI_BASE_ADDRESS_4);
    printk("%08x ",ret);
    //printk("%08x\n",ret);
    printk("\n");
}

void mmain()
{
    uint mem = get_free_page() + 4096;
    printk("This in mmain() Mem is %dM \n", mem / (1024 * 1024));
   trap_init();
   //asm("int $0x2e");
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
    struct hd_cmd_struct cmd = {
        .nsect = 1,
        .sect = 1,
        .driver = 0,
        .cyl = 0,
        .head = 0,
        .cmd = 0x30,
        .intr_addr = &write_intr,
    };
    int b;
    char bb[512];
    u8 r;
    reset_controller();
    cmd.cmd=0x20;
    cmd.intr_addr = &read_intr;
    for (int i = 0;i<1;i++){
        hd_out(&cmd);
        delay();
        cmd.sect = i;
    }

    while(1){
        asm("hlt\t\n");
    }
}
