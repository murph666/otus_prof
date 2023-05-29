#include <iostream>
#include "matrix.h"

int main (int, char **) {
    Matrix<int, 0> matrix;

    auto size = matrix.size();

//    auto a = matrix[0][0];
    std::cout << size;
    return 0;
}
