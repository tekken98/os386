#include <vstring.h>
#include <types.h>
#include <m.h>
#include "mm.h"
static Memory memory;
struct mem_page * free_mem_page = 0;

void * new_mem_page(uint size){
    void *  page = get_free_page();
    struct mem_page * p = (struct mem_page*) page;
    ushort *ps = (ushort *) ((uint)page + sizeof(struct mem_page));
    p->size = size;
    p->free = ps;
    p->next = 0;
    uint count = (4096 - sizeof(struct mem_page)) / (size + 2);
    p->count = count;
    return page;
}

void print_mem_page(mem_page* p){
    printk("size:%x,free:%x,next:%x,count:%d\n",p->size,p->free,p->next,p->count);
    ushort * ps = (ushort*) (p + 1);
    for (uint i = 0;i < p->count;i++)
    {
        ushort d = *(ps+i);
        if ( i > 0 && i % 6 == 0)
            printk("\n");
        printk("[%02x]=%04x ",i,d);
    }

}
void *   kmalloc(uint size){
    if (free_mem_page == 0){
        free_mem_page = (mem_page*)new_mem_page(32);
    }
con:
    struct mem_page * pre = free_mem_page;
    for(; pre != 0;pre = pre->next){
        uint count = size / pre->size + 1;
        uint find=0;
        ushort i = 0;
        for (;i < pre->count;i++){
            if (*(pre->free + i) == 0){
                find++;
                if (find == count){
                    //printk("node is %d \n",i);
                    break;
                }
            }else{
                find = 0;
            }
        }
        if (i < pre->count){
            for (uint j = i + 1  - count ; j < i ;j++){
                *(pre->free +j) = j+1;
            }
            *(pre->free + i) = 0xffff;
            //print_mem_page(pre);
            //printk("mem begin %x \n",(uint)(pre->free + pre->count));
             uint pp = (uint)(pre->free + pre->count) + pre->size * (i + 1 - count);
            return (void*)pp; 
        }
    }
        struct mem_page * n  = (mem_page*)new_mem_page(32);
        n->next = free_mem_page;
        free_mem_page = n;
        goto con;
    return 0;
}
void print_mem(){
    struct mem_page * pre = free_mem_page;
    if (free_mem_page == 0){
        printk(" no call kalloc yet !\n");
        return ;
    }
    for(; pre != 0;pre = pre->next){
        print_mem_page(pre);
    }
    printk("\n");
}
void kfree( void * p){

    if (free_mem_page == 0){
        return ;
    }
    struct mem_page * pre = free_mem_page;
    struct mem_page * cur = (struct mem_page *) ((uint)p & (~4095));
    for(; pre != 0;pre = pre->next){
        if (pre == cur){
            uint space = (uint)p - (uint)(pre->free + pre->count);
            uint node = space / pre->size;
            ushort * begin = pre->free + node;
            ushort * next = 0;
            while((*begin) != 0xffff){
                next  = pre->free +  *begin;
                *begin = 0;
                begin = next;
            }
            *begin = 0;
        }
    }
}
uint get_mem_pages(){
    return sizeof(memory);
}
void free_page(void * addr){
    memory.free_page(addr);
}
void free_pages(void * addr,uint nr){
    memory.free_pages(addr,nr);
}
void *  get_free_page(void){
    return memory.get_free_page();
}
void * get_free_pages(uint nr){
    return memory.get_free_pages(nr);
}
//MEMORY BEGIN
void Memory::free_pages(void * addr,uint nr)
{
    uint p = (uint)addr;
    p -= LOW_MEM;
    p >>= 12;
    for (uint i = 0;i < nr;i++){
        if ( m_mem_map[p + i]--)
            continue ;
        panic("trying to free free page");
    }
}
void * Memory::get_free_pages(uint nr)
{
    uint  *addr ;
    for (uint i = PAGING_PAGES - 1; i > 0;i--){
        if (m_mem_map[i] == 0){
            uint j = i;
            while(--nr > 0 && m_mem_map[j--] == 0 )
                ;
            if (nr > 0){
                i = j;
                continue;
            }
            for (uint k=j;k<=i;k++)
                m_mem_map[k]  = 1;
            addr =(uint *) ((j << 12 ) + LOW_MEM);
            for (uint j = 0; j < 1024 * nr;j++)
                addr[j] = 0;
            return addr;
        }
    }
    return 0;
}
void Memory::panic(cch* err)
{
    printk(err);
}
void Memory::free_page(void * addr)
{
    uint p = (uint)addr;
    p -= LOW_MEM;
    p >>= 12;
    if ( m_mem_map[p]--) return ;
    panic("trying to free free page");
}
Memory::Memory()
{
    for (uint i = 0;i < PAGING_PAGES;i++)
        m_mem_map[i] = 0;
}
void *  Memory::get_free_page(void)
{
    uint  *addr ;
    for (uint i = PAGING_PAGES - 1; i > 0;i--){
        if (m_mem_map[i] == 0){
            m_mem_map[i]  = 1;
            addr =(uint *) ((i << 12 ) + LOW_MEM);
            for (int j = 0; j < 1024;j++)
                addr[j] = 0;
            return addr;
        }
    }
    return 0;
}
//MEMORY END
