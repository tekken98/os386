#include <vstring.h>
#include <types.h>
#include <m.h>
#include "mm.h"
static Memory memory;
struct mem_page * free_mem_page = 0;
struct mem_page {
    int size;
    ushort * free;
    struct mem_page * next;
    uint count;
};
uint new_mem_page(uint size){
    uint page = get_free_page();
    struct mem_page * p = (struct mem_page*) page;
    ushort *ps = (ushort *) (page + sizeof(struct mem_page));
    p->size = size;
    p->free = ps;
    p->next = 0;
    uint count = (4096 - sizeof(struct mem_page)) / (size + 2);
    p->count = count;
    for (int i = 0;i< count;i++){
        *(ps+i) = i+1;
    }
    *(ps+count-1) = 0xffff;
    printk("size %x,%x,%x, %d\n",p->size,p->free,p->next,p->count);
    for (int i = 0;i < count;i++)
    {
        ushort d = *(ps+i);
        printk("[%x]=%x ",i,d);
    }
    return page;
}
    uint  kmalloc(uint size){
    if (free_mem_page == 0){
        free_new_page = new_mem_page(32);
    }
    struct new_mem_page * pre = free_new_page;
    for(; pre != 0;pre = pre->next){
       uint count = size / pre->size + 1;
       uint find=0;
       for (short i = 0;i<pre->count;i++){
           if (*(pre->free + i) == 0){
               find++;
               if (find == count)
                   break;
           }else{
               find = 0;
           }
       }
       if (i < count){
           for (int j = i - count ; j< count;j++){
               *(pre->free +j) = j+1;
           }
           *(pre->free + count - 1) = 0xffff;
           return (uint)(pre->free + pre->count) + pre->size * (i - count);
       }
           
    }
}
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
