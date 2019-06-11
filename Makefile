CFLAGS=-Xassembler --no-pad-sections -Xassembler -R -Wall -fomit-frame-pointer -fstrength-reduce -O
DRIVERS=kernel/chr_drv/chr_drv.a
LDFLAGS=-s -x
INCLUDE=-I/home/bao/prg/linux/include
export INCLUDE
export CFLAGS
img: system.o
	@(cd boot;make)
	@virtualbox --startvm dos &
	@#qemu-system-i386 -fda boot/floppy.img &
	@#--debug-command-line
system.o: boot/header.o init/main.o kernel/kernel.o $(DRIVERS)  mm/mm.o
	@ld -m elf_i386 boot/header.o init/main.o kernel/kernel.o \
		$(DRIVERS) mm/mm.o --entry=_start -Ttext=0 -o bin.o $(LDFLAGS)
	@# ld -m emulation so nice :-?
	@objcopy -S -O binary  -j .got -j .data  -j .text -j .rodata -j .bss bin.o system.o
boot/header.o:boot/header.s
	@nasm -f elf32 $< -l $.lst -o $@
init/main.o:init/main.c
	@(cd init;make)
kernel/kernel.o: 
	@(cd kernel;make)
$(DRIVERS):
	@(cd kernel/chr_drv;make)
mm/mm.o: 
	@(cd mm/;make);
clean:
	-@rm -rf *.o *.lst
	@(cd boot;make clean)
	@(cd kernel;make clean)
	@(cd kernel/chr_drv/;make clean)
	@(cd mm/;make clean)
	@(cd init ;make clean)
dep:
	-@(cd kernel;make dep)
	-@(cd kernel/chr_drv/;make dep)
	-@(cd mm/;make dep)
	-@(cd init ;make dep)
