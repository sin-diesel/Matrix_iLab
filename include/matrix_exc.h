#pragma once

#include <exception>
#include <string>

class MatrixException : public std::exception {
    std::string m_error;
public:
    MatrixException(std::string error): m_error(error) {};
    const char* what() const noexcept override {
        return m_error.c_str();
    }
};