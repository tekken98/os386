FLAGS=-Xassembler --no-pad-sections -Xassembler -R
img:floppy.img bootsect.o setup.o tool
	@./tool
	@virtualbox --startvm dos
bootsect.o:bootsect.s
	@nasm  bootsect.s -l bootsect.lst -o bootsect.o
setup.o: headup.o system.o asm.o traps.o
	ld -m elf_i386 headup.o system.o asm.o traps.o --entry=_start -Ttext=0 -o bin.o
	@# ld -m emulation so nice :-?
	@objcopy -O binary -j .data  -j .text -j .rodata -j .bss bin.o setup.o

headup.o:setup.s
	@nasm -f elf32 setup.s -l setup.lst -o headup.o
system.o:system.c
	@gcc -c system.c -o system.o -m32 $(FLAGS)
asm.o:asm.s 
	@nasm -f elf32 asm.s -l asm.lst -o asm.o
traps.o:traps.c
	gcc -c traps.c -o traps.o -m32  $(FLAGS)
floppy.img: bootsect.o setup.o
	@dd if=/dev/zero of=floppy.img bs=1024 count=1440
tool:tool.c
	@gcc tool.c -o tool -ggdb
clean:
	-@rm -f *.o

