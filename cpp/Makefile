INFONEST_PATH = ../InfoNest/cpp
CXXFLAGS = -std=c++14 -O3 -g -Wall -Wextra -pedantic
OBJECTS = ConstantHazard.o

default:
	g++ $(CXXFLAGS) -I$(INFONEST_PATH) -c ConstantHazard.cpp
	g++ $(CXXFLAGS) -I$(INFONEST_PATH) -c main-constanthazard.cpp
	g++ -L$(INFONEST_PATH) -o main-constanthazard $(OBJECTS) main-constanthazard.o -linfonest
	rm -f *.o
