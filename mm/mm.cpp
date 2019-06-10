#include <vstring.h>
#include <types.h>
#include <m.h>
#include "mm.h"
static Memory memory;
uint get_mem_pages(){
    return sizeof(memory);
}
void free_page(ulong addr){
    memory.free_page(addr);
}
ulong get_free_page(void){
    return memory.get_free_page();
}
//MEMORY BEGIN
void Memory::panic(cch* err)
{
    printk(err);
}
void Memory::free_page(ulong addr)
{
    addr -= LOW_MEM;
    addr >>= 12;
    if ( m_mem_map[addr]--) return ;
    panic("trying to free free page");
}
Memory::Memory()
{
    for (uint i = 0;i < PAGING_PAGES;i++)
        m_mem_map[i] = 0;
}
ulong Memory::get_free_page(void)
{
    uint  *addr ;
    for (uint i = PAGING_PAGES - 1; i > 0;i--){
        if (m_mem_map[i] == 0){
            m_mem_map[i]  = 1;
            addr =(uint *) ((i << 12 ) + LOW_MEM);
            for (int j = 0; j < 1024;j++)
                addr[j] = 0;
            return (int)addr;
        }
    }
    return 0;
}
//MEMORY END
