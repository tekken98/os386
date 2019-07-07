#ifndef M_H
#define M_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif
#define  LOW_MEM 0x200000
#define  PAGING_MEMORY (28 * 1024 * 1024)
#define PAGING_PAGES  ((28*1024*1024) >> 12)
#define  DMA_ADDR  (30*1024 * 1024)
struct mem_page {
    int size;
    ushort * free;
    struct mem_page * next;
    uint count;
};

void * get_free_page(void);
void * get_free_pages(uint nr);
void free_page(void*);
void free_pages(void* addr,uint nr);
void * new_mem_page(uint);
void * kmalloc(uint size);
void kfree(void *);
//void print_mem_page(struct mem_page*);
#ifdef __cplusplus
}
#endif
#endif

