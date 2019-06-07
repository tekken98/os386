FLAGS=-Xassembler --no-pad-sections -Xassembler -R
img: floppy.img tool
floppy.img: bootsect.o setup.o
	@dd if=/dev/zero of=floppy.img bs=1024 count=1440
tool:tool.c
	@gcc $< -o $@ -ggdb
clean:
	-@rm -f *.o *.lst

