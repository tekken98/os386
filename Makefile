FLAGS=-Xassembler --no-pad-sections -Xassembler -R
img:floppy.img bootsect.o setup.o system.o tool
	@./tool
	@virtualbox --startvm dos 
	#--debug-command-line
bootsect.o:bootsect.s
	@nasm  bootsect.s -l bootsect.lst -o bootsect.o
setup.o:setup.s
	@nasm setup.s -l setup.lst -o setup.o
system.o: header.o main.o asm.o traps.o
	ld -m elf_i386 header.o main.o asm.o traps.o --entry=_start -Ttext=0 -o bin.o
	@# ld -m emulation so nice :-?
	@objcopy -O binary -j .data  -j .text -j .rodata -j .bss bin.o system.o
header.o:header.s
	@nasm -f elf32 header.s -l header.lst -o header.o
main.o:main.c
	@gcc -c main.c -o main.o -m32 $(FLAGS)
asm.o:asm.s 
	@nasm -f elf32 asm.s -l asm.lst -o asm.o
traps.o:traps.c
	gcc -c traps.c -o traps.o -m32  $(FLAGS)
floppy.img: bootsect.o setup.o
	@dd if=/dev/zero of=floppy.img bs=1024 count=1440
tool:tool.c
	@gcc tool.c -o tool -ggdb
clean:
	-@rm -f *.o *.lst

