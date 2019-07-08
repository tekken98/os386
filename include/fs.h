#ifndef FS_H
#define FS_H
#include "types.h"
#include "ide.h"
#include "m.h"
struct super_block {
    u32 inode_bitmap_begin;
    u32 inode_bitmap_nr;
    u32 data_bitmap_begin;
    u32 data_bitmap_nr;
    u32 inode_block_begin;
    u32 inode_block_nr;
    u32 data_block_begin;
    u32 data_block_nr;
};
struct super_all {
    struct super_block sb;
    uchar * inode_bitmap;
    uchar * data_bitmap;
}; 
void format(void);
void read_super(struct super_block * super);
void read_super_all();
void write_super_all();
void print_super_info(struct super_block * p );
uint find_first_zero(u32 * buff, u32 size);
uint set_bit(uint index,u32 * data);
int sys_mkdir(const char * pathname);
#endif

