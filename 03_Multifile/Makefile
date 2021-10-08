GENERATES = README prog prog-a prog-so liboutput_static.a liboutput.so test
TRASH = *.o *~ o.*
CFLAGS=-fPIC

all:	README prog prog-a prog-so liboutput_static.a liboutput.so test

README:	prog
	./$< 2> $@

%.o:	%.c
	cc $< -c -o $@ $(CFLAGS)

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@ 

prog:	const.o fun.o prog.o
	cc $^ -o $@

fun.o:	outlib.h

prog-a:	prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

test0:	prog prog-a prog-so
	./prog 2> prog0.out
	./prog-a 2> prog-a0.out
	LD_LIBRARY_PATH=`pwd` ./prog-so 2> prog-so0.out

test1:	prog prog-a prog-so
	./prog olya 2> prog1.out
	./prog-a olya 2> prog-a1.out
	LD_LIBRARY_PATH=`pwd` ./prog-so olya 2> prog-so1.out

test3:	prog prog-a prog-so
	./prog o ly a 2> prog3.out
	./prog-a o ly a 2> prog-a3.out
	LD_LIBRARY_PATH=`pwd` ./prog-so o ly a 2> prog-so3.out

test: test0 test1 test3
	cmp prog0.out prog-a0.out
	cmp prog1.out prog-a1.out
	cmp prog3.out prog-a3.out
	cmp prog-a0.out prog-so0.out
	cmp prog-a1.out prog-so1.out
	cmp prog-a3.out prog-so3.out

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)
