img:bootsect.o system.o setup.o tool floppy 
	./tool
bootsect.o:bootsect.s
	nasm  bootsect.s -l bootsect.lst -o bootsect.o
system.o:system.c
	gcc -c system.c -o system.o -m32
setup.o: setup.s
	nasm -f elf32 setup.s -l setup.lst -o set.o
	ld -m elf_i386 set.o system.o --section-start=.text=0 -o bin.o 
	objcopy -O binary -j .text bin.o setup.o
floppy: 
	dd if=/dev/zero of=floppy.img bs=1024 count=1440
tool:tool.c
	gcc tool.c -o tool -ggdb
