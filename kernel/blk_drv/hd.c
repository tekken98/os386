#define HD_DATA 0x1f0
#define HD_ERROR 0x1f1
#define HD_STATUS 0x1f7
#define HD_CMD 0x3f6
#define HD_CMD_READ 0x22
#define HD_CMD_WRITE 0x32
#include "traps.h"
#include "io.h"
#include "vstring.h"
#include "ide.h"
extern void hd_interrupt(void);
void (*do_hd)();
struct hd_info_struct  hd_info;
u8 hd_buff[512]={0,};
static void init_hd();
void hd_init(void){
    init_hd();
    set_intr_gate(0x2e,&hd_interrupt);
    outb_p(inb_p(0x21)&0xfb,0x21);
    outb(inb_p(0xa1)&0xbf,0xa1);
}
static void init_hd(){
    hd_info.head = 16;
    hd_info.sect =  63;
    hd_info.cyl= 16383;
    hd_info.wpcom=0;
    hd_info.lzon = 0;
    hd_info.ctl = 0x0; 
}
static int controller_ready(void){
    int retry = 10000;
    int ret ;
    while(--retry){
        ret = inb_p(HD_STATUS);
        if ((ret & 0xc0) == 0x40)
            break;
    }
    return retry;
}
void hd_out(struct hd_cmd_struct * p){
    //register int port asm("dx");
    u16 port;
    outb_p(hd_info.ctl,HD_CMD);
    if (!controller_ready()){
        printk("HD controller not ready!\n");
        hd_dump();
        return ;
    }
    do_hd = p->intr_addr; // this one move most front
    port = HD_DATA;
    outb_p(hd_info.wpcom >> 2,++port);
    outb_p(p->nsect,++port);
    outb_p(p->sect,++port);
    outb_p(p->cyl,++port);
    outb_p(p->cyl>>8,++port);
    outb_p(0xa0|(p->driver<<4)|p->head,++port);
    outb(p->cmd,++port);
}
void hd_out_no_wait(struct hd_cmd_struct * p){
    //register int port asm("dx");
    u16 port;
    do_hd = p->intr_addr; // this one move most front
    outb_p(hd_info.ctl,HD_CMD);
    port = HD_DATA;
    outb_p(hd_info.wpcom >> 2,++port);
    outb_p(p->nsect,++port);
    outb_p(p->sect,++port);
    outb_p(p->cyl,++port);
    outb_p(p->cyl>>8,++port);
    outb_p(0xa0|(p->driver<<4)|p->head,++port);
    outb(p->cmd,++port);
}

void init_intr(void){
    printk("hd init\n");
}
void read_intr(void){
    int r = inb(HD_STATUS);
    //printk("hd read %08b \n",r);
    if (( r & 0x08) == 0x08){
        port_read(HD_DATA,&hd_buff,256);
        for (int i = 0;i < 512;i++){
            printk("%02x ",hd_buff[i]);
        }
        printk("\n");
    }
    r = inb(HD_STATUS);
}
void write_intr(void){
    int r = inb(HD_STATUS);
    //printk("hd write %08b \n",r);
    for (int i = 0;i < 512;i++){
       hd_buff[i] = 0x78;
    }
    if ((r & 0x80) == 0x80)
        port_write(HD_DATA,&hd_buff,256);
    r = inb(HD_STATUS);
}
void unexpected_hd_interrupt(void){
    int r = inb(HD_STATUS);
    printk("Unexpected HD interrupt %08b \n",r);
    if (r & 0x1){
       int b = inb(HD_ERROR); 
       printk("HD_ERROR %08b \n",b);
    }
}
int driver_busy(void){
    u32 i;
    for (i=0;i<100000;i++)
        if ((inb_p(HD_STATUS) & 0x80) == 0x0)
            return 0;
    return 1;
}
void reset_controller(void){
    int i;
    outb(4,HD_CMD);
    for(i = 0; i < 100;i++) nop();   // 0x4 -> 0x0 reset
    outb(hd_info.ctl & 0x0f,HD_CMD);
    if (driver_busy())
        printk("busy\n");
    if ((i = inb(HD_ERROR)) != 1){
        printk("reset failed\n");
        hd_dump();
    }
}
void hd_dump(void){
    u16 port = 0x1f1;
    u8 r;
    char *name[8]={"HD_ERROR","HD_NSECTOR","HD_SECTOR",
        "HD_LCYL","HD_HCYL","HD_CURRENT","HD_STATUS"};
   // for (int i = 0;i < 7; i++)
    //    printk("%08s ",name[i]);
    for (int i = 0;i < 7; i++)
        printk("%08x ",port+i);
    printk("\n");
    for (int i = 0;i < 7;i++){
        r = inb_p(port + i);
        printk("%08b ", r);
    }
    printk("\n");
}
void reset_hd(){
    reset_controller();
    struct hd_cmd_struct h_cmd  = {
        .driver = 0,
        .nsect = hd_info.sect,
        .sect = hd_info.sect,
        .cyl = hd_info.cyl,
        .head = hd_info.head,
        .cmd = 0x91,
        .intr_addr=0x0,
    };
    hd_out(&h_cmd);
}
int identify(){
    u16 port = 0x1f2;
    outb_p(0,port++);
    outb_p(0,port++);
    outb_p(0,port++);
    outb_p(0,port++);
    outb_p(0xa0,port++);
    outb(0xec,port);
    u8 r = inb(port);
    if (r == 0){
        printk("driver not existed.\n");
        return 0;
    }
    while(1){
        r = inb(port);
        if ( inb(0x1f4) != 0x0 || inb(0x1f5) != 0x0){
            printk("not ATA \n");
            return 0;
        }
        if ((r&0x80) == 0x0){
                if ((r & 0x8) == 0x8 || (r & 0x1) == 0x1)
                    break;
        }
                
    }
    return 1;
}
void get_hd_cap(){
    char *bb = (char*)kmalloc(512); 
    outb(0x2,HD_CMD);
    outb(0xa0,HD_CURRENT);
    outb(0xec,HD_STATUS);
    u8 r = inb(HD_STATUS);
    while(1){
        r = inb(HD_STATUS);
        if ((r & 0x80) == 0x0)
            break;
    }
    r = inb(HD_STATUS);
    port_read(HD_DATA,bb,256);
    struct hd_identify_struct * pid = (struct hd_identify_struct*)&bb;
    hd_info.head = pid->heads;
    hd_info.sect = pid->sectors_per_track;
    hd_info.cyl = pid->cyls;
    hd_info.ctl = 0x0;
    hd_info.wpcom = 0;
    hd_info.lzon = 0;
    kfree(bb);
}

