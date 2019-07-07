#include "fs.h"
#include "types.h"
#include "vstring.h"
#define INODE_BIT_SIZE 8192   // one page size 1024 * 8
extern struct super_all g_super;
struct inode_struct {
    u32 inums;
    u32 block_index[9];
};
struct dir_entry {
    char name[28];
    u32  inode;
};

uint find_first_zero(u32 * data,u32 size){
    u32 *p = data;
    while(size--){
        if ( (*p) ^ 0xffffffff)
            break;
        p++;
    }
    u32 ret = *p;
    int i;
    for (i = 0;i<32;i++){
       if (((ret >> i ) & 0x1) == 0x0)
           break;
    }
    printk("%d ", ((u32)(p - data))*32 + i);
    return ((u32)(p - data))*32 + i;
}
uint set_bit(uint index,u32 * data){
    u32 p  = index / 32;
    u32 b = index % 32;
    data[p] |= (0x1 << b);
    //return data[p] & (0x1 << b);
}
uint clear_bit(uint index,u32 *data){
    u32 p  = index / 32;
    u32 b = index % 32;
    data[p] &= ~(0x1 << b);
}
struct inode_stuct *  new_inode(){
    struct super_block * sb = g_super.sb;
    struct inode_struct *p = (struct inode_struct *)kmalloc(sizeof(struct inode_struct));
    p->inums = find_first_zero((u32*)g_super.inode_bitmap,sb->inode_block_nr * 1024 / 4);
    set_bit(p->inums,(u32*)g_super.inode_bitmap);
    printk("p->inums %d \n",p->inums);
    return p;
}
uint new_block(){
    struct super_block * sb = g_super.sb;
    uint ret = find_first_zero((u32*)g_super.data_bitmap,sb->data_bitmap_nr * 1024 /4);
    set_bit(ret,(u32*)g_super.data_bitmap);
    printk("data bitmap %d \n",ret);
    return ret;
}
void add_entry(const char * pathname,struct inode_struct * ind){
    struct super_block * sb = g_super.sb;
    struct dir_entry * dir;
    uchar * p =  (uchar*) get_free_page();
    printk(" data_block_begin %d \n",sb->data_block_begin);
    bread(sb->data_block_begin * 2, 2,(u32)p);
    dir = (struct dir_entry*)p;
    int i;
    for (i =0;i < 1024 / 32;i++){
        if (dir[i].name[0] == 0x0)
            break;
    }
    printk("dir[i] is %d \n",i);
    printk("%d %s \n",strlen(pathname),pathname);
    mmemcpy(&(dir+i)->name,(void*)pathname,strlen(pathname));
    (dir+i)->inode = ind->inums;
    bwrite(sb->data_block_begin * 2, 2,(u32)p);

    bread(sb->inode_block_begin * 2, 2,(u32)p);
    mmemcpy((void*)((struct inode_struct *)p + ind->inums),(void*)ind,sizeof(struct inode_struct));
    bwrite(sb->inode_block_begin * 2, 2,(u32)p);
    free_page(p);
    kfree(ind);
    write_super_all();
}
uint find_entry(const char * pathname){
    struct super_block * sb = g_super.sb;
    struct dir_entry * dir;
    uchar * p =  (uchar*) get_free_page();
    bread(sb->data_block_begin * 2, 2,(u32)p);
    dir = (struct dir_entry*)p;
    int i;
    for (i =0;i < 1024 / 32;i++){
        if (dir[i].name[0] != 0x0)
            if (!strcmp(dir[i].name,pathname))
                    return 1;
    }
    return 0;
}
int sys_mkdir(const char * pathname){
    if (find_entry(pathname))
        return 1;
    struct inode_struct *inode;
    inode = new_inode();
    inode->block_index[0] = new_block();
    add_entry(pathname,inode);
    return 0;
}
