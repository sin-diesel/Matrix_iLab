#include <gtest/gtest.h>
#include "matrix.hpp"


TEST(Matrix, Matrix_rowcol_constructor) {
    Matrix<int> m1{5, 6};
    D(m1.dump());
    Matrix<int> m2{2, 3};
    D(m2.dump());

    int num = 0;
    std::cout << "Setting matrix to increasing sequence of numbers " << std::endl;
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 3; ++j) {
            int* elem = m2.get_elem(i, j);
            *elem = num;
            ++num;
        }
    }

    D(m2.dump());
}

TEST(Matrix, Matrix_eye_constructor) {
    std::cout << "Constructing diagonal matrix" << std::endl;
    Matrix<int> m1 = Matrix<int>::eye(10, 5);
    D(m1.dump());
}

TEST(Matrix, Matrix_comparison_op) {
    Matrix<int> m1 = Matrix<int>::eye(10, 5);
    Matrix<int> m2(10, 10);
    for (int i = 1; i <= 10; ++i) {
         int* elem = m2.get_elem(i, i);
         *elem = 5;
     }
    D(m2.dump());

    ASSERT_EQ(m1, m2);
}

TEST(Matrix, Matrix_exc) {
    Matrix<int> m1 = Matrix<int>::eye(10, 5);
    Matrix<int> m2 = Matrix<int>::eye(9, 5);
    try {
        auto eq = m1 == m2;
    } catch (...) {
        std::cout << "Matrix dimension mismatch" << std::endl;
        // How to exit test manually? This is a horrible solution.
        ASSERT_EQ(0, 0);
    }
}

TEST(Matrix, Matrix_sequence) {
    std::vector<int> v = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v.begin(), v.end());
    Matrix<int> m2(2, 2);

    int* elem = m2.get_elem(1,1);
    *elem = 2;
    elem = m2.get_elem(1, 2);
    *elem = 1;
    elem = m2.get_elem(2, 1);
    *elem = 1;
    elem = m2.get_elem(2, 2);
    *elem = 5;

    D(m1.dump());
    D(m2.dump());
    ASSERT_EQ(m1.get_rows(), 2);
    ASSERT_EQ(m1.get_cols(), 2);
    ASSERT_EQ(m1 ,m2);

}

TEST(Matrix, Matrix_braces_op) {
    std::vector<int> v = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v.begin(), v.end());

    ASSERT_EQ(m1[1][1], 2);
    ASSERT_EQ(m1[1][2], 1);
    ASSERT_EQ(m1[2][1], 1);
    ASSERT_EQ(m1[2][2], 5);
}

TEST(Matrix, Matrix_add_op) {
    std::vector<int> v = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v.begin(), v.end());

    std::vector<int> v2 = {5, 5, 5, 5};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());

    std::vector<int> v3 = {7, 6, 6, 10};
    Matrix<int> m3(2, 2, v3.begin(), v3.end());

    m2 += m1;
    ASSERT_EQ(m2, m3);
}

TEST(Matrix, Matrix_copy_constructor) {
    std::vector<int> v1 = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    Matrix<int> m2 = m1;
    D(m1.dump();)
    // std::cout << "Matrix m1 buf: " << m1. << std::endl;
    // std::cout << "Matrix m2 buf: " << std::endl;
    D(m2.dump();)
    ASSERT_EQ(m1, m2);
}

TEST(Matrix, Matrix_add_bin_op) {
    std::vector<int> v1 = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    std::vector<int> v2 = {0, -1, 1, 1};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());

    std::vector<int> v3 = {2, 0, 2, 6};
    Matrix<int> m3(2, 2, v3.begin(), v3.end());

    Matrix<int> m4 = m1 + m2;

    ASSERT_EQ(m4, m3);
}

TEST(Matrix, Matrix_negate_op) {
    std::vector<int> v1 = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    std::vector<int> v2 = {-2, -1, -1, -5};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());

    Matrix<int> m3 = -m1;

    ASSERT_EQ(m2, m3);
}

TEST(Matrix, Matrix_combined_ops) {
    std::vector<int> v1 = {2, 0, 0, 5};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    std::vector<int> v2 = {2, -1, -1, 5};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());

    std::vector<int> v3 = {0, 1, 1, 0};
    Matrix<int> m3(2, 2, v3.begin(), v3.end());

    Matrix<int> m4 = -m1 + m2 + m3;

    Matrix<int> m(2, 2);

    ASSERT_EQ(m, m4);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}