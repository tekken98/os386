#include <stdio.h>
#include<assert.h>
#include<stdlib.h>
int main(){
    unsigned int ret;
    FILE *p = fopen("bootsect.o","r");
    assert(p != NULL);
    fseek(p,0,SEEK_END);
    unsigned int boot_size = ftell(p);
    printf("bootsect size is %d\n",boot_size);
    ret = fseek(p,0,SEEK_SET);

    FILE *op = fopen("floppy.img","r");
    ret = fseek(op,0,SEEK_END);
    unsigned int floppy_size = ftell(op);
    ret = fseek(op,0,SEEK_SET);

    FILE *setup = fopen("setup.o","r");
    assert(setup != NULL);
    fseek(setup,0,SEEK_END);
    unsigned int setup_size = ftell(setup);
    fseek(setup,0,SEEK_SET);
    printf("setup size is 0x%x bytes need %d sectors \n", setup_size,(setup_size + 511) >> 9 );
    FILE *system = fopen("../system.o","r");
    assert(system != NULL);
    fseek(system,0,SEEK_END);
    unsigned int system_size = ftell(system);
    fseek(system,0,SEEK_SET);
    printf("system size is 0x%x bytes need %d sectors \n", system_size,(system_size + 511) >> 9 );

    unsigned int sectors =  ((system_size + 511) >> 9) + (4)  + ((511 + boot_size) >> 9); 
    printf("total need is 0x%0x bytes  %d sectors \n", sectors << 9, sectors);
    char * buff = malloc(floppy_size);
    assert(buff != NULL);
    fread(buff,1,floppy_size,op);
    fread(buff,1,boot_size,p);
    fread(buff + 512,1,setup_size,setup);
    fread(buff + 512 * 4 + 512, 1,system_size,system);

    buff[510] = 0x55;
    buff[511] = 0xaa;
    fclose(op);
    op = fopen("floppy.img","w");
    ret = fwrite(buff,1,floppy_size,op);
    fflush(op);
    fclose(op);
    fclose(p);
    fclose(system);
    fclose(setup);

    if (buff != NULL)
        free(buff);
    assert(op != NULL);
    return 0;
}
