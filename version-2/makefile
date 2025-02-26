build:
	g++ -std=c++14 -c  src/interpreter/*.cpp -Isrc/interpreter -o interpreter.o
	g++ -std=c++14 src/*.cpp interpreter.o -Isrc -o main

dev: build
	./main