#CPP = gcc -E -nostdinc -I../include
#CFLAGS =-Wall -fstrength-reduce -fomit-frame-pointer -I../include
#LDFLAGS =-s -x
CPP = gcc -E  -I../include
.c.o:
%.o : %.cpp
	 @gcc -c $< -o $@ -m32  $(CFLAGS)  $(INCLUDE)
OBJS=
mm.o:$(OBJS)

clean:
	-@rm -f *.o *.lst

dep:
	#-sed '/\#\#\# Dependencies/q' < Makefile >tmp_make
	#-(for i in *.c ; do echo -n `echo $$i|sed 's,\.c,\.s,'`" ";\
		$(CPP) -M $$i;done) >>tmp_make
	#cp tmp_make Makefile
	#rm tmp_make
### Dependencies: 
