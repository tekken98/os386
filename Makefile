FLAGS=-Xassembler --no-pad-sections -Xassembler -R
DRIVERS=kernel/chr_drv/chr_drv.a
LDFLAGS=-s -x -M
all: system
	(cd boot;make)
	@virtualbox --startvm dos 
	#--debug-command-line
system: boot/header.o init/main.o kernel.o $(DRIVERS)
	ld -m elf_i386 boot/header.o init/main.o kernel/kernel.o  \
	$(DRIVERS) --entry=_start -Ttext=0 -o bin.o
	@# ld -m emulation so nice :-?
	@objcopy -O binary -j .data  -j .text -j .rodata -j .bss bin.o system.o
boot/header.o:boot/header.s
	@nasm -f elf32 $< -l $@.lst -o $@
init/main.o:init/main.c
	 gcc -m32 -c $< -o $@  $(FLAGS) 
kernel.o:
	(cd kernel;make)
kernel/chr_drv/chr_drv.a:
	(cd kernel/chr_drv;make)
clean:
	-@rm -rf *.o *.lst
	(cd boot;make clean)
	(cd kernel;make clean)
	(cd init ;make clean)

