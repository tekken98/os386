CFLAGS=-Xassembler --no-pad-sections -Xassembler -R -Wall -fomit-frame-pointer -fstrength-reduce 
CHR_DRIVERS=kernel/chr_drv/chr_drv.a 
BLK_DRIVERS=kernel/blk_drv/blk_drv.a 
PCI=kernel/pci/pci.a
LDFLAGS=-s -x
#LDFLAGS=-s -x -M
pwd:=$(shell pwd)
INCLUDE:=-I$(pwd)/include
CPP = gcc -nostdinc -nostdinc++ -nostdlib -E
#CPP = gcc -E
export INCLUDE
export CFLAGS
export CPP
img: system.o
	@(cd boot;make)
	@#virtualbox --startvm dos &
	@VBoxSDL --startvm dos
	@#qemu-system-i386 -fda boot/floppy.img &
	@#--debug-command-line
system.o: boot/header.o init/main.o kernel/kernel.o $(CHR_DRIVERS)  $(BLK_DRIVERS) $(PCI) mm/mm.o
	@ld -m elf_i386 boot/header.o init/main.o kernel/kernel.o \
		$(CHR_DRIVERS) $(BLK_DRIVERS) $(PCI) mm/mm.o --entry=_start -Ttext=0x100000  -o bin.o $(LDFLAGS)
	@# ld -m emulation so nice :-?
	@objcopy -S -O binary  -j .got -j .data  -j .text -j .rodata -j .bss bin.o system.o
boot/header.o:boot/header.s
	@nasm -f elf32 $< -l $@.lst -o $@
init/main.o:init/main.c
	@(cd init;make)
kernel/kernel.o: 
	@(cd kernel;make)
$(BLK_DRIVERS):kernel/blk_drv/hd.c
	@(cd kernel/blk_drv;make)
$(CHR_DRIVERS):
	@(cd kernel/chr_drv;make)
$(PCI):
	@(cd kernel/pci;make)
mm/mm.o: 
	@(cd mm/;make);
clean:
	-@rm -rf *.o *.lst
	@(cd boot;make clean)
	@(cd kernel;make clean)
	@(cd kernel/chr_drv/;make clean)
	@(cd kernel/blk_drv/;make clean)
	@(cd kernel/pci/;make clean)
	@(cd mm/;make clean)
	@(cd init ;make clean)
dep:
	-@(cd kernel;make dep)
	-@(cd kernel/chr_drv/;make dep)
	-@(cd kernel/blk_drv/;make dep)
	-@(cd kernel/pci/;make dep)
	-@(cd mm/;make dep)
	-@(cd init ;make dep)
