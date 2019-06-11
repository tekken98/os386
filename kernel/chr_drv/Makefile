CFLAGS =-Wall -fno-plt -fstrength-reduce -fomit-frame-pointer  -I../../include
CFLAGS +=-Xassembler --no-pad-sections -Xassembler -R -I../include
#LDFLAGS =-s -x
CPP = gcc -E  -I../include
.s.o:
	@nasm -f elf32 $< -l $@.lst -o $@
.c.o:
	@gcc -c $< -o $@ -m32  $(CFLAGS)
OBJS=keyboard.o console.o
chr_drv.a:$(OBJS)
	@ar rcs --target elf32-i386 chr_drv.a $(OBJS)
clean:
	@rm -rf *.o *.a
dep:
	sed '/\#\#\# Dependencies/q' < Makefile >tmp_make
	(for i in *.c ; do echo -n `echo $$i|sed 's,\.c,\.s,'`" ";\
		$(CPP) -M $$i;done) >>tmp_make
	cp tmp_make Makefile
	rm tmp_make
### Dependencies: 
console.s console.o: console.c /usr/include/stdc-predef.h /usr/include/string.h \
 /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
 /usr/include/features.h /usr/include/x86_64-linux-gnu/sys/cdefs.h \
 /usr/include/x86_64-linux-gnu/bits/wordsize.h \
 /usr/include/x86_64-linux-gnu/bits/long-double.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs.h \
 /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h \
 /usr/include/x86_64-linux-gnu/bits/types/locale_t.h \
 /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h \
 /usr/include/strings.h ../../include/io.h ../../include/tty.h \
 ../../include/types.h
