CFLAGS =-Wall -fno-plt -finline-functions -fomit-frame-pointer  -I../../include
#CFLAGS =-Wall -fno-plt -fstrength-reduce -fomit-frame-pointer  -I../../include
CFLAGS +=-Xassembler --no-pad-sections -Xassembler -R -I../include
#LDFLAGS =-s -x
CPP = gcc -E  -nostdinc -I../../include
.s.o:
	@nasm -f elf32 $< -l $@.lst -o $@
.c.o:
	@gcc -c $< -o $@ -m32  $(CFLAGS)
OBJS=early.o
pci.a:$(OBJS)
	@ar rcs --target elf32-i386 pci.a $(OBJS)
clean:
	@rm -rf *.o *.a 
dep:
	sed '/\#\#\# Dependencies/q' < Makefile >tmp_make
	(for i in *.c ; do echo -n `echo $$i|sed 's,\.c,\.s,'`" ";\
		$(CPP) -M $$i;done) >>tmp_make
	cp tmp_make Makefile rm tmp_make
### Dependencies: 
console.s console.o: console.c ../../include/vstring.h ../../include/types.h \
 ../../include/io.h ../../include/tty.h
