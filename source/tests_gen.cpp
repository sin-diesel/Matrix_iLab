#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <exception>
#include "matrix.hpp"
#include "tests_gen.h"

/*---------------------------------------------------------------*/
Tests::Tests(const std::string name, std::string dim): output_name(name), output_file(output_name) {

    try {
        dimension = std::stoi(dim, nullptr, 10);
    } catch (std::invalid_argument& e) {
        std::cout << "Invalid matrix dimension entered" << std::endl;
        exit(EXIT_FAILURE);
    } catch (std::out_of_range& e) {
        std::cout << "Number entered is out of conversion range" << std::endl;
        exit(EXIT_FAILURE);
    }
    n_elements = dimension * dimension;
};

/*---------------------------------------------------------------*/
void Tests::generate(bool newline) {

    output_file << dimension << " ";
    if (newline) {
        output_file << std::endl;
    }

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(lower_limit, upper_limit);

    /* generating random numbers */
    for (int i = 0; i < n_elements; ++i) {
        if (newline) {
            if (i % dimension == 0 && i != 0) {
                output_file << std::endl;
            }
        }
        int random = distrib(gen);
        output_file << random << " ";
    }

    output_file.close();
}

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Usage: ./testgen N [-newline], where N is matrix dimension,"
                        "newline for printing \n character at the end of each row" << std::endl;
        exit(EXIT_FAILURE);
    }

    bool newl = false;
    if (argc == 3) {
        std::string arg(argv[2]);
        std::string newline("-newline");
        /* if arg == "-newline", print newline at the end of each row */
        if (arg.compare(newline) == 0) {
            newl = true;
        }
        
    }

    std::string input("./tests/random.dat");

    Tests tests(input, argv[1]);
    tests.generate(newl);

    return 0;
}