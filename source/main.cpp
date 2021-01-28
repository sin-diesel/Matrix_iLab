#include <iostream>
#include <iomanip>
#include <gtest/gtest.h>
#include "matrix.hpp"

int main(int argc, char** argv) {   

    /* Commented so it does not interfere with program output when tests are being run */
    // std::cout << "Usage: " << "./matrix N elem_1 elem_2 ... or ./matrix < input_file" << std::endl;

    int N = 0;
    std::vector<double> elems;
    std::cin >> N;
    for (int i = 0; i < N * N; ++i) {
        int elem = 0;
        std::cin >> elem;
        elems.push_back(elem);
    }

    try {
        Matrix<double> matrix(N, N, elems.begin(), elems.end());
        D(matrix.dump());
        double determinant = matrix.determinant();
        std::cout << std::setprecision(0) << std::fixed << determinant << std::endl;
    } catch(MatrixException& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}