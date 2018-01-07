all:
	g++ -c block.cpp -o block.o
	g++ -c blockSet.cpp -o blockSet.o
	g++ block.o blockSet.o lab5.cpp -o cache
	./cache 4 8 f LRU gcc10.din
clean:
	rm block.o blockSet.o cache
