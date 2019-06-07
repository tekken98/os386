FLAGS=-Xassembler --no-pad-sections -Xassembler -R
DRIVERS=kernel/chr_drv/chr_drv.a
LDFLAGS=-s -x -M
all: img
	(cd boot;make)
	@virtualbox --startvm dos 
	#--debug-command-line
bootsect.o:bootsect.s
	@nasm  $< -l $@.lst -o $@
setup.o:setup.s
	@nasm $< -l $@.lst -o $@
img: boot/header.o init/main.o kernel.o $(DRIVERS)
	ld -m elf_i386 boot/header.o init/main.o kernel/kernel.o  \
	$(DRIVERS) --entry=_start -Ttext=0 -o bin.o
	@# ld -m emulation so nice :-?
	@objcopy -O binary -j .data  -j .text -j .rodata -j .bss bin.o system.o
	rm bin.o
boot/header.o:boot/header.s
	@nasm -f elf32 $< -l $@.lst -o $@
kernel/chr_drv/chr_drv.a:
	(cd kernel/chr_drv;make)
kernel.o:
	(cd kernel;make)
init/main.o:init/main.c
	 gcc -m32 -c $< -o $@  $(FLAGS) 
clean:
	-@rm -rf *.o *.lst

