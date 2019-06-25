#ifndef IDE_H
#define IDE_H
#define HD_DATA 0x1f0
#define HD_ERROR 0x1f1
#define HD_NSECTOR 0x1f2
#define HD_SECTOR 0x1f3
#define HD_LCYL 0x1f4
#define HD_HCYL 0x1f5
#define HD_CURRENT 0x1f6
#define HD_STATUS  0x1f7
#define HD_CMD 0x3f6
#define IDE_DMA_READ_CMD 0xc8
#define IDE_DMA_WRITE_CMD 0xca
#define IDE_DMA_READ_START 0x9
#define IDE_IDENTIFY_CMD 0xec
#define IDE_DMA_WRITE_START 0x1
struct dma_dest {
    uint addr;
    uint size;
};
struct hd_info_struct {
    uint head,sect,cyl,wpcom,lzon,ctl;
    u16 major;
    u16 dma_mode;
    u32 max_sector;
};
struct hd_prd {
    u32 addr;
    u32 count:16;
    u32 resrved:15;
    u32 eot:1;
};
struct hd_cmd_struct{
    uint driver,nsect;
    uint head,sect,cyl,cmd;
    void (*intr_addr)(void);
};
struct hd_identify_struct{
    u16 device;
    u16 cyls;
    u16 spec;
    u16 heads;
    u32 retired4;
    u16 sectors_per_track;
    u32 reserved;
    u16 retired9;
    char serial[20];
    u32 retired20;
    u16 obsolete;
    char firmware[8];
    char modelnumber[40];
    u16  w47;
    u16  reserved48;
    u16 cap49;
    u16 cap50;
    u32 obsolete51;
    u16 w53;
    u16 current_cyls;
    u16 current_heads;
    u16 current_sectors_per_track;
    u32 cap_in_sectors;
    u16 w59;
    u32 dw60;
    u16 obsolete62;
};
void hd_get_cap(void);
void hd_init(void);
void hd_out(struct hd_cmd_struct *p);
void hd_out_no_wait(struct hd_cmd_struct * p);
void read_intr(void);
void write_intr(void);
void unexpected_hd_interrupt(void);
int driver_busy(void);
void reset_controller(void);
void hd_dump(void);
void init_intr(void);
void reset_hd(void);
int identify(void);
void ide_read_sectors(u32 beg_sect,u32 sects ,u32 addr);
void ide_write_sectors(u32 beg_sect,u32 sects ,u32 addr);
uint  hd_read_native_max_address();
#define port_read(port,buf,nr) \
    asm("cld;rep;insw"::"d"(port),"D"(buf),"c"(nr):)
#define port_write(port,buf,nr) \
    asm("cld;rep;outsw"::"d"(port),"S"(buf),"c"(nr):)
#endif

