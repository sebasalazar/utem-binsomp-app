CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall
LIBS= -lm -lpqxx -lpq
MKDIR = mkdir -p

directorios:
	$(MKDIR) build dist

clean:
	rm -fr *.o a.out core build/ dist/
Bin.o: directorios Bin.cpp
	$(CXX) $(CXXFLAGS) -c Bin.cpp -o build/Bin.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o
	
all: clean Bin.o main.o
	$(CXX) $(CXXFLAGS) -o dist/programa build/main.o build/Bin.o $(LIBS)
	rm -fr build

.DEFAULT_GOAL := all




