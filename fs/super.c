#include "fs.h"
#include "vstring.h"
#include "m.h"
struct super_all g_super;
void format(void){
    struct super_block * p = (struct super_block*) get_free_page();
    for (int i = 0 ;i< 6;i++)
        bwrite(i * 2 ,2,(ulong)p);
    p->inode_bitmap_begin = 2;
    p->inode_bitmap_nr = 1;
    p->data_bitmap_begin = 3;
    p->data_bitmap_nr = 1;
    p->inode_block_begin = 4;
    p->inode_block_nr = 1;
    p->data_block_begin = 5;
    p->data_block_nr = 8192;
    bwrite(1 * 2 ,2,(ulong)p);
    free_page((ulong)p);
}
void read_super_all(){
    struct super_block *sb;
    sb = g_super.sb = (struct super_block*)kmalloc(sizeof(struct super_block));
    g_super.inode_bitmap = (uchar*)get_free_page();
    g_super.data_bitmap = (uchar*)get_free_page();
    read_super(sb);
    print_super_info(sb);
    bread(sb->inode_bitmap_begin * 2 , sb->inode_bitmap_nr * 2,(ulong)g_super.inode_bitmap);
    bread(sb->data_bitmap_begin * 2, sb->data_bitmap_nr * 2, (ulong)g_super.data_bitmap);
}
void read_super(struct super_block * super){
    struct super_block * p = (struct super_block*) get_free_page();
    bread(1 * 2, 2, (ulong)p);
    *super = *p;
    free_page((ulong)p);
}
void write_super_all(){
    struct super_block *sb = g_super.sb;
    bwrite(sb->inode_bitmap_begin * 2 , sb->inode_bitmap_nr * 2,(ulong)g_super.inode_bitmap);
    bwrite(sb->data_bitmap_begin * 2, sb->data_bitmap_nr * 2, (ulong)g_super.data_bitmap);
}
void print_super_info(struct super_block * p ){
    for(int i = 0;i<sizeof(*p) / 4;i++){
        printk("%d, %d \n",i, *((u32*)p+i));
    }
}
