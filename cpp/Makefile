INFONEST_PATH = ../InfoNest/cpp
CXXFLAGS = -std=c++14 -O3 -Wall -Wextra -pedantic
OBJECTS = ConstantHazard.o ExponentialHazard.o

default:
	g++ $(CXXFLAGS) -I$(INFONEST_PATH) -c ConstantHazard.cpp
	g++ $(CXXFLAGS) -I$(INFONEST_PATH) -c ExponentialHazard.cpp
	g++ $(CXXFLAGS) -I$(INFONEST_PATH) -c main-constanthazard.cpp
	g++ $(CXXFLAGS) -I$(INFONEST_PATH) -c main-exponentialhazard.cpp
	g++ -L$(INFONEST_PATH) -o main-constanthazard $(OBJECTS) main-constanthazard.o -linfonest
	g++ -L$(INFONEST_PATH) -o main-exponentialhazard $(OBJECTS) main-exponentialhazard.o -linfonest
	rm -f *.o
