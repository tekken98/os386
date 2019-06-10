img: floppy.img tool
	@./tool
floppy.img: bootsect.o setup.o
	@dd if=/dev/zero of=floppy.img bs=1024 count=1440 >/dev/null
bootsect.o:bootsect.s
	@nasm  $< -l $@.lst -o $@
setup.o:setup.s
	@nasm $< -l $@.lst -o $@
tool:tool.c
	@gcc $< -o $@ -ggdb
clean:
	-@rm -f *.o *.lst

