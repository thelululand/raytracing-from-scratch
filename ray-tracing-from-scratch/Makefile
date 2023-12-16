output: main.o painter.o
	g++ -std=c++17 -Wall main.o painter.o -o output

main.o: main.cc util.o
	g++ -std=c++17 -c main.cc

painter.o: painter.cc painter.h scene.o util.o
	g++ -std=c++17 -c painter.cc

scene.o: scene.h

util.o: util.h

clean:
	rm *.o output