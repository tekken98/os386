#CPP = gcc -E -nostdinc -I../include
CFLAGS1 =-Wall -O -fomit-frame-pointer -fstrength-reduce
CFLAGS1 +=-Xassembler --no-pad-sections -Xassembler -R -I../include
LDFLAGS =-s -x
CPP = gcc -E -I../include
%.o:%.c
	 @gcc -c $< -o $@ -m32  $(CFLAGS1)  $(INCLUDE)
%.o:%.s
	 @nasm -f elf32 $< -l $@.lst -o $@
OBJS= sys_call.o asm.o traps.o string.o sched.o
kernel.o: $(OBJS)
	@ld -r -m elf_i386 $(OBJS) -o kernel.o  $(LDFLAGS)
clean:
	-@rm -f *.o *.lst
dep:
	sed '/\#\#\# Dependencies/q' < Makefile >tmp_make
	(for i in *.c ; do echo -n `echo $$i|sed 's,\.c,\.s,'`" ";\
		$(CPP) -M $$i;done) >>tmp_make
	cp tmp_make Makefile
	rm tmp_make
### Dependencies: 
sched.s sched.o: sched.c /usr/include/stdc-predef.h ../include/sched.h \
 ../include/processor.h ../include/m.h ../include/types.h \
 ../include/vstring.h
string.s string.o: string.c /usr/include/stdc-predef.h \
 /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h ../include/types.h \
 ../include/console.h ../include/vstring.h ../include/types.h
traps.s traps.o: traps.c /usr/include/stdc-predef.h ../include/types.h \
 ../include/io.h ../include/processor.h ../include/m.h ../include/types.h \
 ../include/vstring.h
