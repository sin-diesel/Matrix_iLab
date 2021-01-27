#include <iostream>
#include <gtest/gtest.h>
#include "matrix.hpp"

int main(int argc, char** argv) {

    std::cout << "Usage: " << "./matrix N elem_1 elem_2 ... or ./matrix < input_file" << std::endl;

    int N = 0;
    std::vector<int> elems;
    std::cin >> N;
    for (int i = 0; i < N * N; ++i) {
        int elem = 0;
        std::cin >> elem;
        elems.push_back(elem);
    }

    try {
        Matrix<int> matrix(N, N, elems.begin(), elems.end());
        matrix.dump();
    } catch(MatrixException& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}