FLAGS=-Xassembler --no-pad-sections -Xassembler -R
.s.o:
	@nasm -f elf32 $< -l $@.lst -o $@
.c.o:
	gcc -c $< -o $@ -m32  $(FLAGS)
OBJS=keyboard.o console.o
chr_drv.a:$(OBJS)
	ar rcs --target elf32-i386 chr_drv.a $(OBJS)
console.s console.o:console.c ../../io.h
clean:
	rm -rf *.o
