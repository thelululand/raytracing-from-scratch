output: main.o painter.o
	g++ -std=c++17 -Wall main.o painter.o -o output

main.o: main.cc util.o vec3.o
	g++ -std=c++17 -c main.cc

painter.o: painter.cc painter.h scene.o util.o vec3.o
	g++ -std=c++17 -c painter.cc

scene.o: scene.h vec3.o

util.o: util.h

vec3.o: vec3.h

clean:
	rm *.o output