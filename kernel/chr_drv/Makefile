.s.o:
	@nasm -f elf32 $< -l $@.lst -o $@
.c.o:
	@gcc -c $< -o $@ -m32  $(CFLAGS)
OBJS=keyboard.o console.o
chr_drv.a:$(OBJS)
	@ar rcs --target elf32-i386 chr_drv.a $(OBJS)
clean:
	@rm -rf *.o *.a
