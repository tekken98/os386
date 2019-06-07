//void trap_init();
#include "../include/string.h"
void mmain()
{
    printk("In main!\n");
    printk("How %x a day!\n",'a');
    printk("this is  0x%08x \n",0x12345);
    trap_init();
}
