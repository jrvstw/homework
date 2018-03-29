main: bigInt.o fib.c
	gcc --std=c11 -pg fib.c bigInt.o -o fib.o

bigInt.o: bigInt.c
	gcc --std=c11 -pg -c bigInt.c -o bigInt.o

clean:
	rm -f bigInt.o fib.o gmon.out
