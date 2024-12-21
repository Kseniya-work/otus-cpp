#define BOOST_TEST_MODULE test_sparse_matrix

#include "sparse_matrix.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_matrix)

BOOST_AUTO_TEST_CASE(default_size) {
    SparseMatrix<int, -1> matrix;
    BOOST_CHECK(matrix.size() == 0); // все ячейки свободны
}

BOOST_AUTO_TEST_CASE(default_value) {
    SparseMatrix<int, -1> matrix;
    auto a = matrix[0][0];
    BOOST_CHECK(a == -1);
}

BOOST_AUTO_TEST_CASE(equal_operator) {
    SparseMatrix<int> matrix;
    ((matrix[100][100] = 314) = 0) = 217;
    BOOST_CHECK(matrix[100][100] == 217);
}

BOOST_AUTO_TEST_CASE(fill) {
    SparseMatrix<int> matrix;
    [[maybe_unused]]auto a = matrix[0][0];
    matrix[0][100] = 317;
    matrix[10][100] = 316;
    matrix[100][100] = 315;
    ((matrix[100][100] = 314) = 0) = 217;
    BOOST_CHECK(matrix.size() == 3);
}

BOOST_AUTO_TEST_CASE(iterable) {
    SparseMatrix<int, -1> matrix;
    matrix[0][10] = 3;
    matrix[1][1] = 4;
    matrix[10][0] = 5;

    for(auto c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        BOOST_CHECK(matrix[x][y] == v);
    }
}

BOOST_AUTO_TEST_SUITE_END()
