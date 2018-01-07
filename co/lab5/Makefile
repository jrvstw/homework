all:
	g++ -c block.cpp -o block.o
	g++ -c blockSet.cpp -o blockSet.o
	g++ block.o blockSet.o lab5.cpp -o a.out
	./a.out 4 8 f LRU gcc10.din
clean:
	rm block.o blockSet.o a.out
