#include "sparse_matrix.h"

#include <iostream>
#include <cassert>


int main(int, char **) {
    // бесконечная матрица int заполнена значениями -1
    SparseMatrix<int, -1> matrix;
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);

    ((matrix[100][100] = 314) = 0) = 217;
    matrix[100][1] = 315;
    matrix[10][100] = 316;
    matrix[0][100] = 317;
    assert(matrix[100][100] == 217);
    assert(matrix.size() == 4);

    for(auto c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }

    return 0;
}
