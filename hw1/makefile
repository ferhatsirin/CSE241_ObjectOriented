all: main

main: main.o
	g++ main.o -o exe

main.o: main.cpp
	g++ -c main.cpp

run:
	./exe

clean:
	rm *.o exe
