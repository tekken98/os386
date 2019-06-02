const int VIDEOADDR=0xb8000;
void printk(const char * msg){
       int i = 0;
       while ( msg[i++] != 0);
       asm( 
               " con: \t\n" 
               " lodsb \t\n" 
               " stosb \t\n" 
               " mov $15,%%al \t\n"   // 15  and $ 15 deferent meaning
               " stosb \t\n" 
               " dec %%cx \t\n" 
               " jnz con \t\n" 
               ::"S"(msg),"D"(VIDEOADDR),"c"(i) );
}
void main()
{
    char * p = "Hi, buddy!";
    printk(p);
}
