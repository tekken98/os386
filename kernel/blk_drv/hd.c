#define HD_DATA 0x1f0
#define HD_ERROR 0x1f1
#define HD_STATUS 0x1f7
#define HD_CMD 0x3f6
#define HD_CMD_READ 0x22
#define HD_CMD_WRITE 0x32
#include "traps.h"
#include "io.h"
#include "vstring.h"
extern void hd_interrupt(void);
void (*do_hd)();
struct hd_info_struct {
    int head,sect,cyl,wpcom,lzon,ctl;
} hd_info;
struct hd_cmd_struct{
    int driver,nsect;
    int head,sect,cyl,cmd;
    void (*intr_addr)(void);
} hd_cmd;
#define port_read(port,buf,nr) \
    asm("cld;rep;insw"::"d"(port),"D"(buf),"c"(nr):"cx","di")
#define port_write(port,buf,nr) \
    asm("cld;rep;outsw"::"d"(port),"S"(buf):"c"(nr):"cx","si")
void hd_init(void){
    set_intr_gate(0x2e,hd_interrupt);
    outb_p(inb_p(0x21)&0xfb,0x21);
    outb(inb_p(0xa1)&0xbf,0xa1);
}
static void init_hd(){
    hd_info.head = 0;
    hd_info.sect = 0;
    hd_info.cyl= 0;
    hd_info.wpcom=0;
    hd_info.lzon = 0;
    hd_info.ctl = 0;
}
static void hd_out(struct hd_cmd_struct * p){
    register int port asm("dx");
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
static void read_intr(void){
}
static void write_intr(void){
}
void unexpected_hd_interrupt(void){
    printk("Unexpected HD interrupt \n");
}
