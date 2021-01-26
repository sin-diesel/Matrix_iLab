
CPP = g++
IDIR = ./include
CPPFLAGS = -std=c++17 -lgtest -lpthread -I $(IDIR)
SRC_DIR = source
INCL_DIR = include
SOURCES = main.cpp unit_tests.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all tests matrix
all:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/main.cpp -o matrix
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/unit_tests.cpp -o tests

tests:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/unit_tests.cpp -o tests

matrix:
	$(CPP) $(CPPFLAGS) $(SRC_DIR)/main.cpp -o matrix

.PHONY: clean
clean:
	rm matrix
	rm tests