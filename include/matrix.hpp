#pragma once

#include <iostream>
#include <iomanip>
#include "matrix_exc.h"

#define DEBUG false

#define D(stmt) if (DEBUG) {stmt;}

//#define RAW_ALLOCATION


/* TODO
1) add exceptions handler when accessing matrix elements DONE
2) add default value initialization DONE
3) add proxy matrix DONE
4) add copy constructor DONE
5) add elem setter 
6) add matrix comparison operator DONE
7) fix allocation problems DONE
8) add exception handler when comparing elements DONE
9) add not only constructor with sequance but also with initilizer list
10) add Matrix traverse function
11) add operator [][] DONE
12) add multiplication by number DONE
13) add constructor with specified element DONE
*/

template<typename T>
class Matrix {

    int m_rows = 0;
    int m_cols = 0;
    /* Continous array */
    T* m_data = nullptr;

    struct ProxyMatrix {
        T* m_row;
        T& operator[](int col) {
            // how to add m_cols bound checking?
            if (col <= 0) {
                throw MatrixException("Invalid argument passed to braces operator");
            }
            // extremely ugly
            return *( (T*) ((char*) m_row + (col - 1) * sizeof(T))); 
        }

        ProxyMatrix(T* row): m_row(row) {};
        };
    
public: 
    Matrix(int rows = 0, int cols = 0, T data = T{});
    static Matrix<T> eye(int dim = 0, T data = T{});
    template<typename It>
    Matrix(int rows = 0, int cols = 0, It begin = nullptr, It end = nullptr);
    Matrix(const Matrix<T>& rhs);


    T* get_elem(int row, int col) const;
    int get_rows() const {
        return m_rows;
    }
    int get_cols() const {
        return m_cols;
    }
    void transpose();

    Matrix<T>& operator+=(const Matrix<T>& rhs);
    Matrix<T>& operator-=(const Matrix<T>& rhs);
    Matrix<T>& operator*=(int n);
    ProxyMatrix operator[](int row) const {
        if (row <= 0 || row > m_rows) {
            throw MatrixException("Invalid argument passed to braces operator");
        }
        return ProxyMatrix( (T*) ((char*) m_data + (row - 1) * m_cols * sizeof(T)));
    }
    Matrix<T> operator-() const;

    ~Matrix() {
        #ifndef RAW_ALLOCATION
        delete[] m_data;
        #else
        free(m_data);
        #endif
    }
    void dump() const;
};

/*---------------------------------------------------------------*/
template<typename T>
void swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

/*---------------------------------------------------------------*/
template<typename T>
void Matrix<T>::transpose() {
    int diag = 1;
    for (int i = 1; i <= m_rows; ++i) {
        for (int j = diag; j <= m_cols; ++j) {
            T* elem_1 = get_elem(i, j);
            T* elem_2 = get_elem(j, i);
            D(std::cout << "Swapping " << *elem_1 << " and " << *elem_2 << std::endl;)
            swap(elem_1, elem_2);
        }
        /* swapping only diagonal elements */
        ++diag;
    }
}

/*---------------------------------------------------------------*/
template<typename T>
Matrix<T>& Matrix<T>::operator*=(int n) {
    for (int i = 1; i <= m_rows; ++i) {
        for (int j = 1; j <= m_cols; ++j) {
            T* elem = get_elem(i, j);
            *elem = *elem * n;
        }
    }
    return *this;
}

/*---------------------------------------------------------------*/
template<typename T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix<T> temp{*this};
    for (int i = 1; i <= m_rows; ++i) {
        for (int j = 1; j <= m_cols; ++j) {
            T* ths = temp.get_elem(i, j);
            T* othr = get_elem(i, j);
            *ths = -(*othr); 
        }
    }
    return temp;
}

/*---------------------------------------------------------------*/
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs): Matrix(rhs.get_rows(), rhs.get_cols()) {
    for (int i = 1; i <= m_rows; ++i) {
        for (int j = 1; j <= m_cols; ++j) {
            T* elem = get_elem(i, j);
            *elem = rhs[i][j];
        }
    }
}

/*---------------------------------------------------------------*/
/* functions that check if two matrices can be added/subtracted together */
template<typename T>
bool equal_dimensions(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    int l_rows = lhs.get_rows();
    int l_cols = lhs.get_cols();
    int r_rows = rhs.get_rows();
    int r_cols = rhs.get_cols();

    if (l_rows != r_rows || l_cols != r_cols) {
        return false;
    }
    return true;
}

/*---------------------------------------------------------------*/
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {

    bool is_equal = equal_dimensions(*this, rhs);
    if (is_equal == false) {
        // a good idea to throw exception?
        throw MatrixException("Invalid dimensions");
    }
    for (int i = 1; i <= m_rows; ++i) {
        for (int j = 1; j <= m_cols; ++j) {
            T* l_elem = get_elem(i, j);
            T* r_elem = rhs.get_elem(i, j);
            *l_elem += *r_elem;
        }
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {

    bool is_equal = equal_dimensions(*this, rhs);
    if (is_equal == false) {
        // a good idea to throw exception?
        throw MatrixException("Invalid dimensions");
    }

    *this += (-rhs);
    return *this;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    Matrix<T> temp{lhs};
    temp += rhs;
    return temp;
}

template<typename T>
Matrix<T> operator*(int num, const Matrix<T>& rhs) {
    Matrix<T> temp{rhs};
    temp *= num;
    return temp;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs, int num) {
    return num * lhs;
}

template<typename T>
template<typename It> // why?
Matrix<T>::Matrix(int rows, int cols, It begin, It end): Matrix(rows, cols) {
    int dist = std::distance(begin, end);
    D(std::cout << "Distance: " << dist << std::endl);
    if (rows * cols != dist) {
        throw MatrixException("Invalid sequence constructor parameters: matrix size "
                                "does not match number of elements");
    }

    for (int i = 1; i <= rows; ++i)
        for (int j = 1; j <= cols; ++j) {
            T* elem = get_elem(i, j);
            *elem = *begin;
            begin++;
        }
}

template<typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    int l_rows = lhs.get_rows();
    int l_cols = lhs.get_cols();
    int r_rows = lhs.get_rows();
    int r_cols = rhs.get_cols();

    if (l_rows != r_rows || l_cols != r_cols) {
        // a good idea to throw exception?
        throw MatrixException("Matrices dimensions are not equal");
    }
    for (int i = 1; i <= lhs.get_rows(); ++i)
        for (int j = 1; j <= lhs.get_cols(); ++j)
            if (*(lhs.get_elem(i, j)) != *(rhs.get_elem(i, j)))
                return false;
    return true;
}


template<typename T>
Matrix<T>::Matrix(int rows, int cols, T data): m_rows(rows), m_cols(cols) {

    if (rows < 0 || cols < 0) {
        throw std::bad_alloc();
    }
    /* Allocate memory for elements, default-initialize built-in types */

    #ifndef RAW_ALLOCATION
    /* How to initialize by default without loop?  This results in seg faults */
    m_data = new T[rows * cols];
    for (int i = 1; i <= m_rows; ++i) {
        for (int j = 1; j <= m_cols; ++j) {
            T* elem = get_elem(i, j);
            *elem = data;
        }
    }
    #else
    m_data = (T*) calloc(rows * cols, sizeof(T));
    for (int i = 1; i <= m_rows; ++i) {
        for (int j = 1; j <= m_cols; ++j) {
            T* elem = get_elem(i, j);
            *elem = 0;
        }
    }
    #endif

}

template<typename T>
Matrix<T> Matrix<T>::eye(int dim, T data) {
    Matrix<T> temp{dim, dim};
    for (int i = 1; i <= dim; ++i) {
        T* elem = temp.get_elem(i, i);
        if (elem == nullptr) {
            std::cout << "Corrupted element in matrix" << std::endl;
        }
        *elem = data;
    }
    return temp;
}


template <typename T>
T* Matrix<T>::get_elem(int row, int col) const {
    /* This is very questionable, as static_cast protects against
       such conversions => using c-ctyle cast */
    return (T*) ((char*) m_data + (row - 1) * m_cols * sizeof(T) + (col - 1) * sizeof(T));
}

template <typename T>
void Matrix<T>::dump() const {
    std::cout << "DUMPING MATRIX " << this << std::endl;
    std::cout << "Rows: " << m_rows << std::endl;
    std::cout << "Cols: " << m_cols << std::endl;
    for (int i = 1; i <= m_rows; ++i) {
        for (int j = 1; j <= m_cols; ++j) {

            T* elem = get_elem(i, j);
            if (elem == nullptr) {
                std::cout << "Matrix element [ " << i << "][" <<
                j << "] is corrupted" <<
                std::endl;
            }
            // may throw an exception? 
            std::cout << std::right << std::setw(5) << *elem << " ";

        }
        std::cout << std::endl;
    }
}