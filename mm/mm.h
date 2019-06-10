#ifndef MM_H
#define MM_H
#include<types.h>
const uint LOW_MEM=0x200000;
const uint PAGING_MEMORY=30 * 1024 * 1024;
const uint PAGING_PAGES = PAGING_MEMORY >> 12;
class Memory
{
    uchar m_mem_map [ PAGING_PAGES] = {0,};
    public:
    Memory();
    inline void invalidate() {asm("mov %%eax,%%cr2"::"a"(0));};
    inline void  copy_page(uint from,uint to){
        asm("cld;rep;movsl"::"S"(from),"D"(to),"c"(1024):"cx","di","si");
    };
    void free_page(ulong addr);
    ulong get_free_page(void);
    void panic(cch* err);
}; 
#endif
