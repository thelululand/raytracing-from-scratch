output: main.o painter.o
	g++ -std=c++0x -Wall main.o painter.o -o output

main.o: main.cc
	g++ -c main.cc

painter.o: painter.cc painter.h
	g++ -c painter.cc

clean:
	rm *.o output