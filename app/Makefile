CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall -fopenmp
LIBS= -lm -lpqxx -lpq -lpthread
MKDIR = mkdir -p

directorios:
	$(MKDIR) build dist

clean:
	rm -fr *.o a.out core build/ dist/

pgPool.o: directorios pgPool.cpp
	$(CXX) $(CXXFLAGS) -c pgPool.cpp -o build/pgPool.o

DBService.o: directorios DBService.cpp
	$(CXX) $(CXXFLAGS) -c DBService.cpp -o build/DBService.o

Bin.o: directorios Bin.cpp
	$(CXX) $(CXXFLAGS) -c Bin.cpp -o build/Bin.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o
	
all: clean DBService.o Bin.o pgPool.o main.o
	$(CXX) $(CXXFLAGS) -o dist/programa \
	    build/main.o build/Bin.o \
	    build/DBService.o build/pgPool.o $(LIBS)
	rm -fr build

.DEFAULT_GOAL := all




