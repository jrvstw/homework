main: fib.c bigInt.c
	gcc --std=c11 -pg fib.c bigInt.c -o fib.o

profile: fib.o
	./fib.o && gprof -b fib.o gmon.out > profile

clean:
	rm -f fib.o gmon.out profile
