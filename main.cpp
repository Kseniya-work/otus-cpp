#include "sparse_matrix.h"

#include <cassert>
#include <cstdio>
#include <iostream>

int main(int, char **) {
    // infinite matrix filled with 0 values
    SparseMatrix<int> matrix;
    assert(matrix.size() == 0); // all cells are free
    auto a = matrix[0][0];
    assert(a == 0);
    assert(matrix.size() == 0);

    std::size_t n = 10;
    for (std::size_t i = 0; i < n; i++)
    {
        matrix[i][i] = i;
        matrix[i][n - 1 - i] = n - 1 - i;
    }

    for (std::size_t i = 1; i < n - 1; i++)
    {
        for (std::size_t j = 1; j < n - 1; j++)
            std::cout << matrix[i][j] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;

    assert(matrix.size() == 18); // default elements are not taken into account
    std::cout << "size = " << matrix.size() << std::endl;

    for(auto c: matrix)
    {
        int i;
        int j;
        int v;
        std::tie(i, j, v) = c;
        std::printf("m[%d][%d] = %d\n", i, j, v);
    }

    return 0;
}
