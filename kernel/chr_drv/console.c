#include "vstring.h"
#include "io.h"
#include "tty.h"
#include "sched.h"
const int VIDEOADDR=0xb8000;
const int VIDEOWIDTH=80;
const int VIDEOHEIGHT=24;
const int video_port_val = 0x3d5;
const int video_port_reg= 0x3d4;
const int video_mem_start=0xb8000;
int current_row = 0;
int current_col = 0;
tty_queue tty_queue_buff = {0,0,0,{0}};
void writeScreen(const char * begin, int len );
void setCursor(void);
void do_tty_interrupt(uint a);
void backspace();

void clear(){
    uint count = VIDEOWIDTH * (VIDEOHEIGHT+1) ;
    for (uint i = 0; i < count;i++){
        *((uchar*)VIDEOADDR+i*2) = 0x0;
        *((uchar*)VIDEOADDR+i*2+1) = 15;
    }
    current_row = current_col = 0;
}
struct task_struct * tty_task;
void tty_put_char(uchar c){
   tty_queue * p = &tty_queue_buff;
   if (((p->head+1) & (TTY_BUF_SIZE-1)) != p->tail){
       p->buf[p->head++] = c;
       p->head &= (TTY_BUF_SIZE - 1);
   }
}
uchar tty_get_char(){
   uchar c=0x0;
   tty_queue * p = &tty_queue_buff;
   if (p->head == p->tail)
       sleep_on(&tty_task);
   if (p->head != p->tail){
       c  = p->buf[p->tail++];
       p->tail &= (TTY_BUF_SIZE - 1);
    }
   return c;
}
void do_tty_interrupt(uint a){
    //printk("tty_interrupt\n");
    tty_put_char((uchar)a);
    wake_up(&tty_task);
}
void pause(){
    tty_get_char();
    tty_get_char();
}
int getPos(){
       return current_row * VIDEOWIDTH * 2 + current_col * 2 + VIDEOADDR;
}

void writeWithReturn(const char * msg ){
    int c;
    const char * p = msg;
    const char * e;
    int flag=0;
    while ((c = *msg++)) {
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
       if (len == 0) return;
       if (current_row > VIDEOHEIGHT){
           scrollup();
           current_row--;
       }
       int pos = getPos();
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
       if (current_row > VIDEOHEIGHT){
           scrollup();
           current_row--;
       }
       setCursor();
}
void backspace(){
    if (current_col == 0 && current_row > 0){
        current_col = VIDEOWIDTH;
        current_row--;
    }
    else
        current_col--;
    int pos = getPos();
    *(unsigned char *) pos = ' ';
    *(unsigned char *) (pos + 1) = 15;
    setCursor();

}
void write(int row,int col , const char * str){
    current_row = row;
    current_col = col;
    writeWithReturn(str);
}


void setCursor(void){
    cli();
    int pos = getPos();
    outb_p(14,video_port_reg);
    outb_p(0xff&((pos-video_mem_start) >>9),video_port_val);
    outb_p(15,video_port_reg);
    outb_p(0xff&((pos-video_mem_start)>>1),video_port_val);
    *(unsigned char*)(pos+1) = 10;
    sti();
}
void scrollup(void){
    asm("rep movsl\t\n"::"S"(VIDEOADDR + VIDEOWIDTH * 2),"D"(VIDEOADDR),"c"(VIDEOWIDTH * (current_row)/2));
    asm("rep stosl\t\n"::"a"(0),"D"(VIDEOADDR + VIDEOWIDTH * 24 * 2),"c"(VIDEOWIDTH /2));
}
