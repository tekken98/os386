CFLAGS=-Xassembler --no-pad-sections -Xassembler -R
DRIVERS=kernel/chr_drv/chr_drv.a
LDFLAGS=-s -x -M
INCLUDE=-I/home/bao/prg/linux/include/
export INCLUDE
export CFLAGS
all: system
	@(cd boot;make)
	@virtualbox --startvm dos 
	@#qemu-system-i386 -fda boot/floppy.img
	@#--debug-command-line
system: boot/header.o init/main.o kerneldir chr_drvdir mmdir
	@ld -m elf_i386 boot/header.o init/main.o kernel/kernel.o  \
	$(DRIVERS) mm/mm.o --entry=_start -Ttext=0 -o bin.o
	@# ld -m emulation so nice :-?
	@objcopy -O binary -j .data  -j .text -j .rodata -j .bss bin.o system.o
boot/header.o:boot/header.s
	@nasm -f elf32 $< -l $@.lst -o $@
init/main.o: init/main.c
	@(cd init;make)
kerneldir:
	@(cd kernel;make)
chr_drvdir:
	@(cd kernel/chr_drv;make)
mmdir:
	@(cd mm/;make);
clean:
	-@rm -rf *.o *.lst
	@(cd boot;make clean)
	@(cd kernel;make clean)
	@(cd kernel/chr_drv/;make clean)
	@(cd mm/;make clean)
	@(cd init ;make clean)

