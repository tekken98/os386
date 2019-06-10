#include <stdarg.h>
#include "types.h"
#include "console.h"
#include "vstring.h"
void writeWithReturn(char * );
char buff [1024]={0};
static char alpha[] = "0123456789ABCDEF";
void mmemcpy(void* dst, void* src,uint len){
    asm(
            "mov %%ecx,%%ebx \t \n"
            "and 0xf,%%ebx \t \n"
            "shr $02,%%cx \t\n"
            "rep movsl \t\n"
            "mov %%ebx,%%ecx \t\n"
            "rep movsb \t\n"
            ::"c"(len),"S"(src),"D"(dst));
}
uint toString(char *buf,int d, uint radical,char fill,
        ushort count){
    char digit[16];
    char *p = buf;
    int i = 0;
    int n;
    while ( n = d % radical, d = d / radical){
        digit[i++] = n;
    }
    digit[i] = n;
    for (int j = i; j < count - 1;j++)
    {
        *p++ = fill;
    }

    for (int j = 0; j <= i; j++)
        p[j] = alpha[digit[i-j]];
    //return   count > i + 1 ? count:i+1;
    return   max(count,i+1);
}
uint toStringInt(char *buf,uint d,char fill,
        unsigned short count){
    return toString(buf,d,10,fill,count);
}
uint toStringHex(char * buf,uint d,char fill,
        unsigned short count){
    return toString(buf,d,16,fill,count);
}
void mvsprintf(char * buf, const char * fmt, va_list va){
    char c;
    int flag=0;
    int i = 0;
    uint d;
    char *s;
    char ch;
    char fill='0';
    ushort count=0;
    while(c = *fmt++){
        if ( c!='%'){
            buf[i++] = c;
            continue;
        } 
con:
        c = *fmt++;
        switch(c){
            case 's':
                s = va_arg(va,char*);
                while(buf[i++] = *s++)
                    ;
                i--;
                break;
            case 'd':
                d = va_arg(va,unsigned int);
                d = toStringInt(&buf[i],d,fill,count);
                i += d ;
                fill='0';
                count=0;
                break;
            case 'x':
x:
                d = va_arg(va,int);
                d = toStringHex(&buf[i],d,fill,count);
                i += d ;
                fill='0';
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
