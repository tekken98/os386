#CPP = gcc -E -nostdinc -I../include
#CFLAGS =-Wall -fstrength-reduce -fomit-frame-pointer -I../include
#LDFLAGS =-s -x
CPP = gcc -E -nostdinc  -I../include

main.o:main.c
	echo $(INCLUDE)
	@gcc -m32 -c $< -o $@  $(CFLAGS) $(INCLUDE)
clean:
	-@rm -rf *.o
dep:
	sed '/\#\#\# Dependencies/q' < Makefile >tmp_make
	(for i in *.c ; do echo -n `echo $$i|sed 's,\.c,\.s,'`" ";\
		$(CPP) -M $$i;done) >>tmp_make
	cp tmp_make Makefile
	rm tmp_make
### Dependencies: 
main.s main.o: main.c ../include/vstring.h ../include/types.h ../include/m.h \
 ../include/types.h ../include/processor.h
