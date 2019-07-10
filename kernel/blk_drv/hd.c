//TRAITS
//void hd_init(void)
//static void init_hd()
//static int controller_ready(void)
//void hd_out(struct hd_cmd_struct * p)
//void hd_out_no_wait(struct hd_cmd_struct * p)
//void init_intr(void)
//void read_intr(void)
//void write_intr(void)
//void unexpected_hd_interrupt(void)
//int driver_busy(void)
//void reset_controller(void)
//void hd_dump(void)
//void reset_hd()
//int identify()
#include "sched.h"
#include "traps.h"
#include "io.h"
#include "vstring.h"
#include "ide.h"
#include "m.h"
struct task_struct * waiting;
extern void hd_interrupt(void);
void (*do_hd)();
struct hd_info_struct  hd_info;
u8 hd_buff[512]={0,};
static void init_hd();
struct dma_dest dmadest;

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
    hd_info.max_sector  = hd_read_native_max_address(); 
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
        //hd_dump();
        return ;
    }
    do_hd = p->intr_addr; // this one move most front
    port = HD_DATA;
    outb_p(hd_info.wpcom >> 2,++port);
    outb_p(p->nsect,++port);
    outb_p(p->sect,++port);
    outb_p(p->cyl,++port);
    outb_p(p->cyl>>8,++port);
    outb_p(0x40|(p->driver<<4)|p->head,++port); // LBA begin from 0 sector. CHS begin from 1 sector.
    outb(p->cmd,++port);
}

void init_intr(void){
    printk("hd init\n");
}
void read_intr(void){
    outb(0x0,0xd000);
    int r = inb(HD_STATUS);
    //printk("hd read %08b \n",r);
    //hd_dump();
    mmemcpy((void*)dmadest.addr , (void*)DMA_ADDR, dmadest.size);
    if (( r & 0x08) == 0x08){
        port_read(HD_DATA,&hd_buff,256);
        for (int i = 0;i < 512;i++){
            //printk("%02x ",hd_buff[i]);
        }
        //printk("\n");
    }
    wake_up(&waiting);
}
void write_intr(void){
    outb(0x0,0xd000);
    //int r = inb(HD_STATUS);
    //printk("hd write %08b \n",r);
    /*
    for (int i = 0;i < 512;i++){
       hd_buff[i] = 0x78;
    }
    if ((r & 0x80) == 0x80)
        port_write(HD_DATA,&hd_buff,256);
        */
    //r = inb(HD_STATUS);
    wake_up(&waiting);
}
void unexpected_hd_interrupt(void){
    int r = inb(HD_STATUS);
    //printk("Unexpected HD interrupt %08b \n",r);
    if (r & 0x1){
       //int b = inb(HD_ERROR); 
       //printk("HD_ERROR %08b \n",b);
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
        //hd_dump();
    }
}
void hd_dump(void){
    u16 port = 0x1f1;
    u8 r;
    //char *name[8]={"HD_ERROR","HD_NSECTOR","HD_SECTOR", "HD_LCYL","HD_HCYL","HD_CURRENT","HD_STATUS"};
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
void hd_get_cap(){
    u16 *bb = (u16*)kmalloc(512); 
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
    hd_info.major = bb[80];
    hd_info.dma_mode = bb[88];
    if (hd_info.major & (0x1 << 6))
        printk("support atapi-6\n");
    printk("%016b\n", bb[88]);
    u32 size = hd_info.head * hd_info.sect * hd_info.cyl;
    printk("size if %d bytes \n",size * 512);
    printk("currents sectors %d bytes \n",(*((u32*)&bb[60]))* 512);
    kfree(bb);
}
void ide_read_sectors(u32 beg_sect,u32 sects ,u32 addr){
    u16 dma_base = 0xd000;
    struct hd_cmd_struct cmd ={
        .nsect = sects,
        .sect = beg_sect & 0xff,
        .cyl = (beg_sect) >> 8 & 0xffff,
        .head = (beg_sect) >> 24 & 0xf,
        .cmd = IDE_DMA_READ_CMD,
        .intr_addr=&read_intr,
    };
    reset_controller();
    struct hd_prd * table = (struct hd_prd *)kmalloc(sizeof(struct hd_prd));
    table->addr = DMA_ADDR;
    table->count= sects << 9;
    table->eot = 0x1;
    dmadest.addr = addr;
    dmadest.size = sects << 9;
    outl((u32)table,dma_base+4);
    outb(0x6,dma_base+2);
    hd_out(&cmd);
    outb(0x9,dma_base); 
    sleep_on(&waiting);
    kfree(table);
    //u8 r = inb(dma_base + 2);
    //printk("%08b\n",r);
}
void ide_write_sectors(u32 beg_sect,u32 sects ,u32 addr){
    u16 dma_base = 0xd000;
    struct hd_cmd_struct cmd ={
        .nsect = sects,
        .sect = beg_sect & 0xff,
        .cyl = (beg_sect) >> 8 & 0xffff,
        .head = (beg_sect) >> 24 & 0xf,
        .cmd = IDE_DMA_WRITE_CMD,
        .intr_addr=&write_intr,
    };
    reset_controller();
    struct hd_prd * table = (struct hd_prd *)kmalloc(sizeof(struct hd_prd));
    mmemcpy((void*)DMA_ADDR,(void*)addr,sects<<9);
    table->addr = DMA_ADDR;
    table->count= sects << 9;
    table->eot = 0x1;
    dmadest.addr = addr;
    dmadest.size = sects << 9;
    outl((u32)table,dma_base+4);
    outb(0x6,dma_base+2);
    hd_out(&cmd);
    outb(IDE_DMA_WRITE_START,dma_base); 
    sleep_on(&waiting);
    kfree(table);
    //u8 r = inb(dma_base + 2);
    //printk("%08b\n",r);
}
uint hd_read_native_max_address(void){
    //u16 dma_base = 0xd000;
    struct hd_cmd_struct cmd = {};
    cmd.cmd = 0xf8;
    reset_controller();
    outb(6,HD_CMD);
    hd_out(&cmd);
    sleep_on(&waiting);
   u32 sector =  (inb(HD_DATA + 3 )) | ((inb(HD_DATA + 4 ) << 8)) | ((inb(HD_DATA + 5) << 16)) | ( (u32)(inb(HD_DATA + 6) & 0xf)<<24);
   return sector;
}
