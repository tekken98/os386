img:bootsect.o setup.o tool
	@./tool
bootsect.o:bootsect.s
	@nasm  bootsect.s -l bootsect.lst -o bootsect.o
system.o:system.c
	@gcc -c system.c -o system.o -m32
setup.o: headup.o system.o
	@ld -m elf_i386 headup.o system.o -Ttext=0 -o bin.o 
	@# ld -m emulation so nice :-?
	@objcopy -O binary -j .text -j .rodata bin.o setup.o
headup.o:setup.s
	@nasm -f elf32 setup.s -l setup.lst -o headup.o
floppy: bootsect.o setup.o
	@dd if=/dev/zero of=floppy.img bs=1024 count=1440
tool:tool.c
	@gcc tool.c -o tool -ggdb
clean:
	-@rm -f *.o

