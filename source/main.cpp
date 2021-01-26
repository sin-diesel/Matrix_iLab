#include <iostream>
#include <gtest/gtest.h>
#include "matrix.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << "./matrix N elem_1 elem_2 ... or ./matrix N < input_file";
    }

    return 0;
}