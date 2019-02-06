all : main

main : main.o ConnectFourAbstract.o Cell.o ConnectFourPlus.o ConnectFourPlusUndo.o ConnectFourDiag.o
	g++ main.o ConnectFourAbstract.o Cell.o ConnectFourPlus.o ConnectFourPlusUndo.o ConnectFourDiag.o -o exe

main.o : main.cpp
	g++ -std=c++11 -c main.cpp

ConnectFourPlus.o : ConnectFourPlus.cpp
	g++ -std=c++11 -c ConnectFourPlus.cpp

ConnectFourPlusUndo.o : ConnectFourPlusUndo.cpp
	g++ -std=c++11 -c ConnectFourPlusUndo.cpp

ConnectFourDiag.o : ConnectFourDiag.cpp
	g++ -std=c++11 -c ConnectFourDiag.cpp

ConnectFourAbstract.o : ConnectFourAbstract.cpp
	g++ -std=c++11 -c ConnectFourAbstract.cpp

Cell.o : Cell.cpp
	g++ -std=c++11 -c Cell.cpp

run :
	./exe

clean :
	rm *.o exe


