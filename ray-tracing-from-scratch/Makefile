output: main.o painter.o
	g++ -std=c++0x -Wall main.o painter.o -o output

main.o: main.cc sphere.o canvas.o
	g++ -c main.cc

sphere.o: sphere.h canvas.o

painter.o: painter.cc painter.h canvas.o
	g++ -c painter.cc

canvas.o: canvas.h

clean:
	rm *.o output