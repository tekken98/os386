#include <stdarg.h>
#include "types.h"
#include "console.h"
#include "vstring.h"
char buff [1024]={0};
char alpha[] = "0123456789ABCDEF";
void mmemcpy(void* dst, void* src,uint len){
    asm(
            "mov %%ecx,%%ebx \t \n"
            "and $0x3,%%ebx \t \n"
            "shr $02,%%cx \t\n"
            "rep movsl \t\n"
            "mov %%ebx,%%ecx \t\n"
            "rep movsb \t\n"
            ::"c"(len),"S"(src),"D"(dst):"ebx");
    //printk("%p,%p,%d\n",dst,src,len);
    return ;
}
uint strlen(const char * str){
    uint c = 0;
    while(*str++)
        c++;
    return c;
}
uint strcmp(const char * first , const char * second){
    if (strlen(*first) != strlen(*second))
        return 1;
    while(*first++ == *second++ ){
        if (*first == 0x0 )
            if (*second == 0x0)
                return 0;
            else
                return 1;
    }
    return 1;
}
uint toString(char *buf,int d, uint radical,char fill,
        ushort count,char sepchar){
    uchar digit[16];
    char *p = buf;
    int i = 0;
    int n;
    while ( n = d % radical, d = d / radical){
        digit[i++] = n;
    }
    digit[i] = n;
    uint sep =  max(count,i+1);
    sep %= 4;
    if (sep > 0)
        sep = 4 - sep;
    for (int j = i; j < count - 1;j++)
    {
        if (sepchar){
            if ( sep > 0 && sep % 4 == 0) {
                *p++ = sepchar;
            }
            sep++;
        }
        *p++ = fill;
    }
    for (int j = 0; j <= i; j++){
        if(sepchar){
            if (sep > 0 && sep % 4 == 0 && j+1 < i) {
                *p++ = sepchar;
            }
            sep++; // this one is make c += ((sep -1) /4); if sep is 4 or 8 ...
        }
        *p++ = alpha[digit[i-j]];
    }
    //return   count > i + 1 ? count:i+1;
    int c =  max(count,i+1);
    if (sepchar)
        c += ((sep - 1) / 4);
    return c;
}

uint toStringBin(char *buf,uint d,char fill,
        unsigned short count,char sepchar){
    return toString(buf,d,2,fill,count,sepchar);
}
uint toStringInt(char *buf,uint d,char fill,
        unsigned short count,char sepchar){
    return toString(buf,d,10,fill,count,sepchar);
}
uint toStringHex(char * buf,uint d,char fill,
        unsigned short count,char sepchar){
    return toString(buf,d,16,fill,count,sepchar);
}
void mvsprintf(char * buf, const char * fmt, va_list va){
    char c;
    int i = 0;
    uint d;
    char *s;
    char fill='0';
    char sep = 0x0;
    ushort count=0;
    while((c = *fmt++)){
        if ( c!='%'){
            buf[i++] = c;
            continue;
        } 
con:
        c = *fmt++;
        switch(c){
            case 's':
                s = va_arg(va,char*);
                while((buf[i++] = *s++))
                    ;
                i--;
                break;
            case 'b':
                d = va_arg(va,unsigned int);
                d = toStringBin(&buf[i],d,fill,count,sep);
                i += d ;
                fill='0';
                sep=0x0;
                count=0;
                break;
            case 'd':
                d = va_arg(va,unsigned int);
                d = toStringInt(&buf[i],d,fill,count,sep);
                i += d ;
                fill='0';
                sep=0x0;
                count=0;
                break;
            case 'x':
x:
                d = va_arg(va,int);
                d = toStringHex(&buf[i],d,fill,count,sep);
                i += d ;
                fill='0';
                sep=0x0;
                count=0;
                break;
            case 'c':
                d  = va_arg(va,unsigned int);
                buf[i++]=(unsigned char)d;
                break;
            case '0':
                fill = '0';
                count = (unsigned short)((*fmt++) - '0');
                while ( '0' <= *fmt  && *fmt <= '9'){
                    count = count * 10 +  ((unsigned short)(*fmt) - '0');
                    fmt++;
                }
                goto con;
            case 'p':
                fill='0';
                count = 8;
                buf[i++]='0';
                buf[i++]='x';
                goto x;
            case 'S':
                sep = *fmt++;
                goto con;
            default:
                break;
        }
    }
    buf[i] = 0x0;
}
void __stack_chk_fail_local(){};
void printk(const char * str,...){
    va_list va;
    va_start(va,str);
    mvsprintf(buff,str,va);
    va_end(va);
    writeWithReturn(buff);
}
void print_mem( void * p,uint size){
    int i = 0;
    while (size--){
            printk("%02x",*((uchar*)p + i++));
            if (i % 16 == 0){
                printk("\n");
            }else
                printk(" ");
    }
    if (size % 16 > 0){
        printk("\n");
    }
}
