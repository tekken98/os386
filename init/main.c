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
        .cyl = 0,
        .head = 0,
        .driver = 0,
        .cmd = 0xc8,
        .intr_addr = &read_intr,
    };
    reset_controller();
    //get_hd_cap();

    char * t = (char*)kmalloc(512);
    struct hd_prd * table = (struct hd_prd *) kmalloc(sizeof(struct hd_prd) + 16);
    for (int i = 0; i < 512;i++)
         t[i] = 0x78;
    printk("%x\n",t);
    printk("table is %x\n",table);
    table = (u32)table + 16;
    table = (u32)table & 0xfffffff0;
    printk("after table is %x\n",table);
        table->addr = (u32)t,
        table->count = 512,
        table->eot = 0x1;
    u16 dma_base = 0xd000;
cona:
    outl((u32)table,dma_base+4);
    outb(0x6,dma_base+2);
    hd_out(&cmd);
    outb(0x9,dma_base);
    delay();
    //hd_dump();
    u8 r = inb(dma_base + 2);
    //printk(" dma status %08b\n",r);
    int *i = 0;
    while(1){
        if ((*i++ == 0x03020100) && (*i == 0x07060504))
            break;
        if ((u32)i > (u32)t)
            goto cona;
    }
    //t = --i;
    printk("%x \n",t);
    for (int j = 0; j < 32;j++)
        printk("%x ", (u8)t[j]);
    while(1){
        asm("hlt\t\n");
    }
}
