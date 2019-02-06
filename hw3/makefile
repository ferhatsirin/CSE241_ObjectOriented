all : main

main : main.o ConnectFour.o
	g++ main.o ConnectFour.o -o exe

main.o : main.cpp
	g++ -std=c++11 -c main.cpp

ConnectFour.o : ConnectFour.cpp
	g++ -std=c++11 -c ConnectFour.cpp

run :
	./exe

clean :
	rm *.o exe


