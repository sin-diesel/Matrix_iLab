
CPP = g++
IDIR = ./include
CPPFLAGS = -std=c++17 -lgtest -lpthread -I $(IDIR)
SRC_DIR = source
INCL_DIR = include
SOURCES = main.cpp unit_tests.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all test matrix testgen
all:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/main.cpp -o matrix
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/unit_tests.cpp -o test

test:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/unit_tests.cpp -o test

matrix:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/main.cpp -o matrix

testgen:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/tests_gen.cpp -o testgen

.PHONY: clean
clean:
	rm matrix
	rm tests