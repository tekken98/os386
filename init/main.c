void trap_init();
#include "string.h"
void mmain()
{
    printk("In main!\n");
    printk("How %c a day!\n",'a');
    trap_init();
}
