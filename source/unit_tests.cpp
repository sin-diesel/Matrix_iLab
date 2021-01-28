#include <gtest/gtest.h>
#include "matrix.hpp"

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_rowcol_constructor) {
    Matrix<int> m1{5, 6, 56};
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

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_eye_constructor) {
    std::cout << "Constructing diagonal matrix" << std::endl;
    Matrix<int> m1 = Matrix<int>::eye(10, 5);
    D(m1.dump());
}

/*---------------------------------------------------------------*/
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

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_exc) {
    try {
        Matrix<int> m1 = Matrix<int>::eye(10, 5);
        Matrix<int> m2 = Matrix<int>::eye(10, 5);
        auto eq = m1 == m2;
    } catch (MatrixException& e) {
        std::cout << e.what() << std::endl;
        // How to exit test manually? This is a horrible solution.
        ASSERT_EQ(1, 0);
    }
}

/*---------------------------------------------------------------*/
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

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_braces_op) {
    std::vector<int> v = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v.begin(), v.end());

    ASSERT_EQ(m1[1][1], 2);
    ASSERT_EQ(m1[1][2], 1);
    ASSERT_EQ(m1[2][1], 1);
    ASSERT_EQ(m1[2][2], 5);
}

/*---------------------------------------------------------------*/
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

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_copy_constructor) {
    std::vector<int> v1 = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    Matrix<int> m2 = m1;
    D(m1.dump());
    // std::cout << "Matrix m1 buf: " << m1. << std::endl;
    // std::cout << "Matrix m2 buf: " << std::endl;
    D(m2.dump());
    ASSERT_EQ(m1, m2);
}

/*---------------------------------------------------------------*/
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

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_negate_op) {
    std::vector<int> v1 = {2, 1, 1, 5};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    std::vector<int> v2 = {-2, -1, -1, -5};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());

    Matrix<int> m3 = -m1;

    ASSERT_EQ(m2, m3);
}

/*---------------------------------------------------------------*/
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

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_mult_by_num) {
    std::vector<int> v1 = {1, -1, -1, 1};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    std::vector<int> v2 = {2, -2, -2, 2};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());

    Matrix<int> m3 = m1 * 2;
    D(m3.dump());
    Matrix<int> m4 = 2 * m1;
    D(m4.dump());

    ASSERT_EQ(m3, m2);
    ASSERT_EQ(m4, m2);
}

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_sub_op) {
    std::vector<int> v1 = {2, -2, -2, 2};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());
    D(m1.dump());

    std::vector<int> v2 = {1, 1, 1, 1};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());
    D(m2.dump());

    std::vector<int> v3 = {1, -3, -3, 1};
    Matrix<int> m3(2, 2, v3.begin(), v3.end());
    D(m3.dump());

    m1 -= m2;
    D(m1.dump());
    ASSERT_EQ(m1, m3);
}

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_transpose) {
    std::vector<int> v1 = {1, 0, 1, 2};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    std::vector<int> v2 = {1, 1, 0, 2};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());

    D(m1.dump());
    m1.transpose();
    D(m1.dump());
    ASSERT_EQ(m1, m2);
}

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_elem_access) {
    std::vector<int> v1 = {1, 0, 1, 2};
    Matrix<int> m1(2, 2, v1.begin(), v1.end());

    try {
        auto elem = m1[1][1];
    } catch (MatrixException& e) {
        std::cout << e.what() << std::endl;
        // How to exit test manually? This is a horrible solution.
        ASSERT_EQ(1, 0);
    }
}

/*---------------------------------------------------------------*/
TEST(Matrix, Matrix_reorder) {
    std::vector<int> v1 = {0, 0, 1, 2, 2, 2, 1, 1, 0};
    Matrix<int> m1(3, 3, v1.begin(), v1.end());

    D(m1.dump());
    std::vector<int> v2 = {2, 2, 2, 0, 0, 1, 1, 1, 0};
    Matrix<int> m2(3, 3, v2.begin(), v2.end());

    reorder(m1);
    D(m1.dump());

    ASSERT_EQ(m1, m2);
}

TEST(Matrix, Matrix_sub_constructror) {
    std::vector<int> v1 = {0, 0, 1, 2, 2, 2, 1, 1, 0};
    Matrix<int> m1(3, 3, v1.begin(), v1.end());

    std::vector<int> v2 = {2, 2, 1, 0};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());

    D(m1.dump());
    Matrix<int> m3 = Matrix<int>::submatrix(m1, 2, 2);
    D(m2.dump());
    ASSERT_EQ(m3, m2);

    m3 = Matrix<int>::submatrix(m1, 1, 1);
    D(m3.dump());
}

TEST(Matrix, Matrix_reorder_submatrix) {
    std::vector<int> v1 = {1, 1, 1, 2, 0, 0, 1, 1, 0};
    Matrix<int> m1(3, 3, v1.begin(), v1.end());
    D(std::cout << "Original: " << std::endl;)
    D(m1.dump());

    std::vector<int> v2 = {1, 0, 0, 0};
    Matrix<int> m2(2, 2, v2.begin(), v2.end());
    D(std::cout << "Expected: " << std::endl;)
    D(m2.dump());

    reorder(m1, 2, 2);
    D(std::cout << "Original reordered: " << std::endl;)
    D(m1.dump());

    Matrix<int> m3 = Matrix<int>::submatrix(m1, 2, 2);
    D(std::cout << "Submatrix from original: " << std::endl;)
    D(m3.dump());

    ASSERT_EQ(m3, m2);
}

TEST(Matrix, Matrix_upper) {
    std::vector<double> v1 = {1, 2, 4, 3, 8, 14, 2, 6, 13};
    Matrix<double> m1(3, 3, v1.begin(), v1.end());

    std::vector<double> v2 = {1, 2, 4, 0, 2, 2, 0, 0, 3};
    Matrix<double> m2(3, 3, v1.begin(), v1.end());

    D(std::cout << "Original: " << std::endl;)
    D(m1.dump());
    gauss(m1);
    ASSERT_EQ(m1, m2);
}

TEST(Matrix, Matrix_lower) {
    std::vector<double> original = {1, 2, 4, 3, 8, 14, 2, 6, 13};
    Matrix<double> m_original(3, 3, original.begin(), original.end());

    std::vector<double> upper = {1, 2, 4, 0, 2, 2, 0, 0, 3};
    Matrix<double> m_upper(3, 3, upper.begin(), upper.end());


    D(std::cout << "Original: " << std::endl;)
    D(m_original.dump());
    D(std::cout << "Upper: " << std::endl;)
    D(m_upper.dump());
    Matrix<double> low = lower(m_original, m_upper);

    std::vector<double> ans = {1, 0, 0, 3, 1, 0, 2, 1, 1};
    Matrix<double> m_ans(3, 3, ans.begin(), ans.end());

    ASSERT_EQ(low, m_ans);
}

TEST(Matrix, Matrix_decompose) {
    std::vector<double> v = {11, 9, 24, 2, 1, 5, 2, 6, 3, 17, 18, 1, 2, 5, 7, 1};
    Matrix<double> m(4, 4, v.begin(), v.end());

    std::vector<double> vl = {1.0000, 0.0000, 0.0000, 0.0000,
                              0.0909, 1.0000, 0.0000, 0.0000,
                              0.2727, 3.4782, 1.0000, 0.0000,
                              0.1818, 0.8043, 0.2302, 1.0000};
    Matrix<double> ml(4, 4, vl.begin(), vl.end());

    std::vector<double> vu = {11.0000, 9.0000, 24.0000, 2.0000,
                              0.0000,  4.1818, -0.1818, 5.8182,
                              0.0000,  0.0000,  12.0869, -19.7826,
                              0.0000,  0.0000,   0.0000, 0.5107};
    Matrix<double> mu(4, 4, vu.begin(), vu.end());

    auto LU = decompose(m);
    Matrix<double> L = std::get<0>(LU);
    Matrix<double> U = std::get<1>(LU);

    ASSERT_EQ(L, ml);
    ASSERT_EQ(U, mu);
}

TEST(Matrix, Matrix_determinant_1) {
    std::vector<double> v = {11, 9, 24, 2, 1, 5, 2, 6, 3, 17, 18, 1, 2, 5, 7, 1};
    Matrix<double> m(4, 4, v.begin(), v.end());

    auto LU = decompose(m);
    Matrix<double> L = std::get<0>(LU);
    Matrix<double> U = std::get<1>(LU);

    double determinant = m.determinant();
    ASSERT_EQ(static_cast<int>(determinant), 284);
}

TEST(Matrix, Matrix_determinant_2) {
    std::vector<double> v = {10, -23, 0, 43, 21,
                             11, 12, -34, 20, 21,
                              -21, -5, -8, 8, 7,
                               3, 1, -4, -21, -22,
                               0, 21, 45, 32, 5};
    Matrix<double> m(5, 5, v.begin(), v.end());

    auto LU = decompose(m);
    Matrix<double> L = std::get<0>(LU);
    Matrix<double> U = std::get<1>(LU);

    double determinant = m.determinant();
    D(std::cout << "Determinant: " << determinant << std::endl);
    ASSERT_EQ(static_cast<int>(determinant), -29052944);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}