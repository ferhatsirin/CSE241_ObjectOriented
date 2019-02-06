all : main

main : main.o
	g++ main.o -o exe

main.o : main.cpp
	g++ -std=c++11 -c main.cpp

run :
	./exe

clean : 
	rm *.o exe 



