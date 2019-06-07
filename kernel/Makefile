FLAGS=-Xassembler --no-pad-sections -Xassembler -R
.c.o:
	 gcc -c $< -o $@ -m32  $(FLAGS) 
.s.o:
	nasm -f elf32 $< -l $@.lst -o $@
OBJS= sys_call.o traps.o asm.o string.o
kernel.o: $(OBJS)
	ld -r -m elf_i386 $(OBJS) -o kernel.o
	# -r no this cant't work
	#ld -r -m elf_i386 $(OBJS) --entry=_start -Ttext=0 -o bin.o
	# ld -m emulation so nice :-?
	#@objcopy -O binary -j .data  -j .text -j .rodata -j .bss bin.o system.o
clean:
	-@rm -f *.o *.lst

