#CPP = gcc -E -nostdinc -I../include
#CFLAGS =-Wall -fstrength-reduce -fomit-frame-pointer -I../include
#LDFLAGS =-s -x
CPP = gcc -nostdinc -nostdinc++ -nostdlib  -I../include
.c.o:
%.o : %.cpp
	 $(CPP) -c $< -o $@ -m32  $(CFLAGS)  $(INCLUDE)
OBJS=
mm.o:$(OBJS)

clean:
	-@rm -f *.o *.lst

dep:
	-sed '/\#\#\# Dependencies/q' < Makefile >tmp_make
	-(for i in *.cpp ; do echo -n `echo $$i|sed 's,\.cpp,\.s,'`" ";\
		$(CPP) -M $$i;done) >>tmp_make
	cp tmp_make Makefile
	rm tmp_make
### Dependencies: 
mm.s mm.o: mm.cpp ../include/vstring.h ../include/types.h ../include/types.h \
 ../include/m.h mm.h
