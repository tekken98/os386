#ifndef MM_H
#define MM_H
#include<types.h>
#include "m.h"
class Memory
{
    uchar m_mem_map [ PAGING_PAGES] = {0,};
    public:
    Memory();
    inline void invalidate() {asm("mov %%eax,%%cr2"::"a"(0));};
    inline void  copy_page(uint from,uint to){
        asm("cld;rep;movsl"::"S"(from),"D"(to),"c"(1024):"cx","di","si");
    };
    void free_page(void * addr);
    void free_pages(void * addr,uint nr);
    void *  get_free_page(void);
    void * get_free_pages(uint nr);
    void panic(cch* err);
}; 
#endif
