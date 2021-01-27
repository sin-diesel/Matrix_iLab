#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <exception>
#include "matrix.hpp"

class Tests {
    int lower_limit = -20;
    int upper_limit = 20;
    int dimension = 0;
    int n_elements = 0;

    std::string output_name;
    std::ofstream output_file;

    /* generate diagonal matrix */
    bool eye = false;

public:
    Tests(const std::string name, std::string dim);
    ~Tests() { 
        output_file.close();
    };

    void generate();

};
