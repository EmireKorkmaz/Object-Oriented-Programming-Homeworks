all: ConnectFour

ConnectFour: main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o
	g++ -std=c++11 main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

ConnectFourAbstract.o: ConnectFourAbstract.cpp
	g++ -c -std=c++11 ConnectFourAbstract.cpp

ConnectFourPlus.o: ConnectFourPlus.cpp
	g++ -c -std=c++11 ConnectFourPlus.cpp

ConnectFourDiag.o: ConnectFourDiag.cpp
	g++ -c -std=c++11 ConnectFourDiag.cpp

ConnectFourPlusUndo.o: ConnectFourPlusUndo.cpp
	g++ -c -std=c++11 ConnectFourPlusUndo.cpp

Cell.o: Cell.cpp
	g++ -c -std=c++11 Cell.cpp

clean:
	rm *.o exe
