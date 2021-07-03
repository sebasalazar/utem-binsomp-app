CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall
LIBS= -lm -lpqxx -lpq
MKDIR = mkdir -p

directorios:
	$(MKDIR) build dist

clean:
	rm -fr *.o a.out core build/ dist/

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o
	
all: clean main.o
	$(CXX) $(CXXFLAGS) -o dist/programa build/main.o $(LIBS)
	rm -fr build

.DEFAULT_GOAL := all




