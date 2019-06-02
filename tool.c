#include <stdio.h>
#include<assert.h>
#include<stdlib.h>
int main(){
    int ret;
    FILE *p = fopen("bootsect.o","r");
    assert(p != NULL);
    fseek(p,0,SEEK_END);
    int size = ftell(p);
    printf("bootsect size is %d\n",size);
    ret = fseek(p,0,SEEK_SET);
    FILE *op = fopen("floppy.img","r");
    ret = fseek(op,0,SEEK_END);
    int osize = ftell(op);
    ret = fseek(op,0,SEEK_SET);
    FILE *setup = fopen("setup.o","r");
    assert(setup != NULL);
    fseek(setup,0,SEEK_END);
    int setup_size = ftell(setup);
    fseek(setup,0,SEEK_SET);
    printf("setup size is %d \n",setup_size);
    printf("total is 0x%0x \n",setup_size + size);
    char * buff = malloc(osize);
    assert(buff != NULL);
    fread(buff,1,osize,op);
    fread(buff,1,size,p);
    fread( buff + 512,1,setup_size,setup);
    buff[510] = 0x55;
    buff[511] = 0xaa;
    fclose(op);
    op = fopen("floppy.img","w");
    ret = fwrite(buff,1,osize,op);
    fflush(op);
    fclose(op);
    fclose(p);

    if (buff != NULL)
        free(buff);
    assert(op != NULL);
    return 0;
}
