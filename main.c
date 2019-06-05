#include <stdarg.h>
const int VIDEOADDR=0xb8000;
const int VIDEOWIDTH=80;
const int VIDEOHEIGHT=24;
int current_row = 0;
int current_col = 0;
char* buff = 0;
static char alpha[] = "0123456789ABCDEF";

void printk(const char * fmt,...);
void trap_init();
void writeScreen(const char * begin, int len );

void writePos(const char * msg ){
    int c;
    const char * p = msg;
    const char * e;
    int flag=0;
    while (c = *msg++) {
        if (c == '\n'){
            if (flag==1){
                current_row++;
                continue;
            }
            e = msg - 1;
            writeScreen(p,(int)(e - p));
            current_row++;
            current_col=0;
            p = msg;
            flag=1;
        }
        flag = 0;
    }
    int len = msg - 1 - p;
    if (len > 0 ) 
        writeScreen(p,len);
}
void writeScreen(const char * begin, int len ){
       int i = 0;
       if (len == 0) return;
       if (current_row > VIDEOHEIGHT / 2){
           current_row = 0;
           current_col = 0;
       }
       int pos = current_row * VIDEOWIDTH * 2 + current_col * 2 + VIDEOADDR;
       asm( 
               " con: \t\n" 
               " lodsb \t\n" 
               " stosb \t\n" 
               " mov $15,%%al \t\n"   // 15  and $ 15 deferent meaning
               " stosb \t\n" 
               " dec %%cx \t\n" 
               " jnz con \t\n" 
               ::"S"(begin),"D"(pos),"c"(len) );
       current_row += (len + current_col)  / VIDEOWIDTH;
       current_col = (len + current_col) % VIDEOWIDTH;;
}

void write(int row,int col , const char * str){
    current_row = row;
    current_col = col;
    writePos(str);
}
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
            default:
                break;
        }
    }
    buf[i] = 0x0;
}
void __stack_chk_fail_local(void){
}
void printk(const char * str,...){
    va_list va;
    va_start(va,str);
    mvsprintf(buff,str,va);
    va_end(va);
    writePos(buff);
}
void mmain()
{
    printk("In main!\n");
    printk("How a day!\n");
    trap_init();
}
