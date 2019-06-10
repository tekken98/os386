.c.o:
	 @gcc -c $< -o $@ -m32  $(CFLAGS)  $(INCLUDE)
.s.o:
	 @nasm -f elf32 $< -l $@.lst -o $@
OBJS= sys_call.o traps.o asm.o string.o sched.o
kernel.o: $(OBJS)
	@ld -r -m elf_i386 $(OBJS) -o kernel.o
clean:
	-@rm -f *.o *.lst

