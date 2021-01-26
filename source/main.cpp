#include <iostream>
#include <gtest/gtest.h>
#include "matrix.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << "./matrix N elem_1 elem_2 ... or ./matrix N < input_file";
    }

    int N = 0;
    std::vector<int> elems;
    std::cin >> N;
    for (int i = 0; i < N * N; ++i) {
        int elem = 0;
        std::cin >> elem;
        elems.push_back(elem);
    }

    Matrix<int> matrix(N, N, elems.begin(), elems.end());
    matrix.dump();
    return 0;
}