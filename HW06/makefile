all: HW6

HW6: main.o
	g++ -std=c++11 main.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

clean:
	rm *.o exe
