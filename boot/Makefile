floppy.img: bootsect.o setup.o ../system.o tool
	@dd if=/dev/zero of=floppy.img bs=1024 count=1440 >/dev/null
	@./tool
bootsect.o:bootsect.s
	@nasm  $< -l $@.lst -o $@
setup.o:setup.s
	@nasm $< -l $@.lst -o $@
tool:tool.c
	@gcc $< -o $@ -ggdb
clean:
	-@rm -f *.o *.lst

