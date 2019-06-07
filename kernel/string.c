#include <stdarg.h>
#include "../include/console.h"
char buff [1024]={0};
static char alpha[] = "0123456789ABCDEF";
unsigned int toString(char *buf,int d, unsigned int radical){
    char digit[16];
    int i = 0;
    int n;
    while ( n = d % radical, d = d / radical){
       digit[i++] = n;
    }
    digit[i] = n;
    for (int j = 0; j <= i; j++)
        buf[j] = alpha[digit[i-j]];
    return i + 1;
}
unsigned int toStringInt(char *buf,unsigned int d){
    return toString(buf,d,10);
}
unsigned int toStringHex(char * buf,unsigned  int d){
    return toString(buf,d,16);
}
void mvsprintf(char * buf, const char * fmt, va_list va){
    char c;
    int flag=0;
    int i = 0;
    while(c = *fmt++){
        if ( c!='%'){
                buf[i++] = c;
                continue;
        } 
        c = *fmt++;
        unsigned int d;
        char *s;
        char ch;
        switch(c){
            case 's':
                s = va_arg(va,char*);
                while(buff[i++] = *s++)
                    ;
                break;
            case 'd':
                d = va_arg(va,unsigned int);
                d = toStringHex(&buf[i],d);
                i += d ;
                break;
            case 'x':
                d = va_arg(va,int);
                buf[i++] = '0';
                buf[i++] = 'X';
                d = toStringHex(&buf[i],d);
                i += d ;
                break;
            case 'c':
                d  = va_arg(va,unsigned int);
                buf[i++]=(unsigned char)d;
                break;
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
    writePos(buff);
}
