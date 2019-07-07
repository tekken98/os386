#include "vstring.h"
#include "m.h"
#include "types.h"
#include "sched.h"
#include "console.h"
#include "pci.h"
#include "ide.h"
#include "io.h"
#include "fs.h"
extern void trap_init(void);
//static struct task_struct init_task = INIT_TASK;
struct task_struct * task[10]={0};
struct task_struct * sleep_task = NULL;
int count = 0;
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
void one();
void run_command(char * command){
    char * argv[16];
    while( *command++ == ' ');
    command--;
    int i = 0;
    argv[i++] = command;
    while( *command != 0x0){
        if ( *command == ' '){
            *command = 0x0;
            while( *++command == ' ');
            argv[i++] = command;
        }else
            command++;
    }
    if (strcmp(argv[0],"format") == 0){
        printk("\n run format\n");
        format();
    }else if (strcmp(argv[0],"mkdir") == 0){
        printk("\n run mkdir \n");
        sys_mkdir(argv[1]);
    }else if (strcmp(argv[0],"cls") == 0){
        clear();
    }

    printk("\n>");
}
void init(){
    char console_buff[256];
    int i = 0;
   uchar c;
   //format();
   read_super_all();
   printk("\n>");
   while(1){
        c = tty_get_char();
        if ( c & 0x80 )
            continue;
        if (c == 0x0)
            continue;
        if (c == 0xd){
            console_buff[i] = 0x0;
            run_command(console_buff);
            i = 0;
        }else{
            console_buff[i++] = c;
            printk("%c",c);
        }
        //exit(1);
   }
}
void three(){
    while(1){
        delay();
        printk("<");
        sleep_on(&sleep_task);
        printk(">");
    }
}
void two(){
    while(1){
        delay();
        printk("(");
        sleep_on(&sleep_task);
        printk(")");
    }
}
void one(){
    char * addr = (char*) kmalloc(512);
    bread(0,1,(ulong)addr);
    printk("hello %s\n",addr);
    kfree(addr);
    while(1){
        delay();
        printk("D");
    }
}
void printbuff(char *addr,uint len){
    for (int i = 0;i < len;i++)
        printk("%02x ",(u8)addr[i]);
}
void mmain()
{
    uint mem = (uint)get_free_page() + 4096;
    clear();
    printk("This in os386 Mem is %dM \n", mem / (1024 * 1024));
    trap_init();
    //mmemcpy(current,&init_task, sizeof(struct task_struct));
    for (int i = 0; i< 10;i++)
        task[i] = 0;
    task[0] = current;
    start_thread(init);
   // start_thread(three);
   // start_thread(two);
   // start_thread(one);
    while(1){
        asm("hlt\t\n");
    }
}
