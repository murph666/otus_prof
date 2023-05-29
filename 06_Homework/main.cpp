#include <iostream>
#include "matrix.h"

int main (int, char **) {
    int const def_value = 0;
    Matrix<int, def_value> matrix;

    auto size = matrix.size();

    auto a = matrix[0][0];
    std::cout << size;

    matrix[100][100] = 314;
    return 0;
}
