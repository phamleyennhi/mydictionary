output: main.o binarySearch.o
	g++ main.o binarySearch.o -o mydictionary

main.o: main.cpp
	g++ -c main.cpp

binarySearch.o: binarySearch.cpp binarySearch.h
	g++ -c binarySearch.cpp 

clean:
	rm *.o output