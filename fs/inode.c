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
    return ((u32)(p - data))*32 + i;
}
uint set_bit(uint index,u32 * data){
    u32 p  = index / 32;
    u32 b = index % 32;
    int ret =  data[p] & (0x1 << b);
    data[p] |= (0x1 << b);
    return ret;
}
uint clear_bit(uint index,u32 *data){
    u32 p  = index / 32;
    u32 b = index % 32;
    uint ret = data[p] &  (0x1 << b);
    data[p] &= ~(0x1 << b);
    return ret;
}
struct inode_struct *  new_inode(){
    struct super_block * sb = &g_super.sb;
    struct inode_struct *p = (struct inode_struct *)kmalloc(sizeof(struct inode_struct));
    //printk("kmalloc %p \n",p);
    p->inums = find_first_zero((u32*)g_super.inode_bitmap,sb->inode_block_nr * 1024 / 4);
    set_bit(p->inums,(u32*)g_super.inode_bitmap);
    return p;
}
void rm_inode(uint inode){
    clear_bit(inode,(u32*)g_super.inode_bitmap);
}
uint new_block(){
    struct super_block * sb = &g_super.sb;
    uint ret = find_first_zero((u32*)g_super.data_bitmap,sb->data_bitmap_nr * 1024 /4);
    set_bit(ret,(u32*)g_super.data_bitmap);
    return ret + sb->data_block_begin;
}
void rm_block(uint inode){
    struct super_block * sb = &g_super.sb;
    struct inode_struct * dir;
    uchar * p = get_free_page();
    bread(sb->inode_block_begin * 2, 2,(u32)p);
    dir = (struct inode_struct *) p;
    dir += inode;
    uint blocknr;
    for (int i = 0;i<7;i++){
        if ((blocknr = dir->block_index[i]) != 0)
            clear_bit(blocknr - sb->data_block_begin,(u32*)g_super.data_bitmap);
    }
}
void add_entry(const char * pathname,struct inode_struct * ind){
    struct super_block * sb = &g_super.sb;
    struct dir_entry * dir;
    uchar * p =  (uchar*) get_free_page();
    bread(sb->data_block_begin * 2, 2,(u32)p);
    dir = (struct dir_entry*)p;
    int i = 0;
    for (i =0;i < 1024 / 32;i++){
        if (dir[i].name[0] == 0x0)
            break;
    }
    //printk("i is %d \n",i);
    mmemcpy(&(dir+i)->name,(void*)pathname,strlen(pathname));
    (dir+i)->inode = ind->inums;
    bwrite(sb->data_block_begin * 2, 2,(u32)p);

    bread(sb->inode_block_begin * 2, 2,(u32)p);
    mmemcpy((void*)((struct inode_struct *)p + ind->inums),(void*)ind,sizeof(struct inode_struct));
    bwrite(sb->inode_block_begin * 2, 2,(u32)p);
    free_page(p);
    write_super_all();
}
int find_entry(const char * pathname, int remove){
    struct super_block * sb = &g_super.sb;
    struct dir_entry * dir;
    uchar * p =  (uchar*) get_free_page();
    bread(sb->data_block_begin * 2, 2,(u32)p);
    dir = (struct dir_entry*)p;
    int i;
    for (i =0;i < 1024 / 32;i++){
        if (dir[i].name[0] != 0x0)
            if (!strcmp(dir[i].name,pathname)){
                    if (remove == 1){
                        dir[i].name[0] = 0x0;
                        bwrite(sb->data_block_begin * 2, 2,(u32)p);
                    }
                    free_page(p);
                    return dir[i].inode;
            }
    }
    free_page(p);
    return -1;
}
int sys_mkdir(const char * pathname){
    if (find_entry(pathname,0) != -1)
        return 1;
    struct inode_struct *inode;
    inode = new_inode();
    inode->block_index[0] = new_block();
    add_entry(pathname,inode);
    kfree(inode);
    return 0;
}
void rm_entry(const char * pathname, uint inode){
    rm_block(inode);
    rm_inode(inode);
    write_super_all();
}
int sys_rmdir(const char * pathname){
    uint inode;
    if ((inode = find_entry(pathname,1)) == -1)
        return 1;
    rm_entry(pathname,inode);
    return 0;
}
int sys_ls(){
    struct super_block * sb = &g_super.sb;
    struct dir_entry * dir;
    uchar * p =  (uchar*) get_free_page();
    bread(sb->data_block_begin * 2, 2,(u32)p);
    dir = (struct dir_entry*)p;
    int i;
    for (i =0;i < 1024 / 32;i++){
        if (dir[i].name[0] != 0x0)
            printk("%s ",dir[i].name);
        }
    printk("\n");
    free_page(p);
    return -1;
}
