#CPP = gcc -E -nostdinc -I../include
CFLAGS1 =-Wall -fomit-frame-pointer -fstrength-reduce
CFLAGS1 +=-Xassembler --no-pad-sections -Xassembler -R -I../include
LDFLAGS =-s -x
CPP = gcc -E -I../include
%.o:%.c
	 @gcc -c $< -o $@ -m32  $(CFLAGS1)  $(INCLUDE)
%.o:%.s
	 @nasm -f elf32 $< -l $@.lst -o $@
OBJS= super.o inode.o
fs.o: $(OBJS)
	@ld -r -m elf_i386 $(OBJS) -o $@  $(LDFLAGS)
clean:
	-@rm -f *.o *.lst
dep:
	sed '/\#\#\# Dependencies/q' < Makefile >tmp_make
	(for i in *.c ; do echo -n `echo $$i|sed 's,\.c,\.s,'`" ";\
		$(CPP) -M $$i;done) >>tmp_make
	cp tmp_make Makefile
	rm tmp_make
### Dependencies: 
