#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include "matrix.hpp"

int main(int argc, char** argv) {
    std::string input(argv[1]);

    int dimension = std::stoi(input, nullptr, 10);

    std::ofstream output("test_data.dat");
    
    output << dimension << " ";

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(-20, 20);

    for (int i = 0; i < dimension * dimension; ++i) {
        int random = distrib(gen);
        output << random << " ";
    }

    output.close();

}