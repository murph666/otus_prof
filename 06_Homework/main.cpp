#include "matrix.h"

#include <iostream>
#include <cassert>

int main (int, char **) {

    Matrix<int, -1> matrix;
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);
    // выведется одна строка
    // 100100314
    for(auto &c: matrix)
    {
        printf("[%d][%d] = %d", c.second.row(), c.second.col(), c.second.get_value());
    }
    std::cout << std::endl;

    int x;
    int y;

    for (x = 0; x < 10; ++x) {
        matrix[x][x] = x;
        int t = 9 - x;
        matrix[x][t] = t;
    }

    for (x = 1; x < 9; ++x) {
        for (y = 1; y < 9; ++y) {
            std::cout << ' ' << matrix[x][y];
        }

        std::cout << std::endl;
    }

    std::cout << "matrix non-default values number: " << matrix.size() << std::endl;
    std::cout << std::endl;

    for (auto& c : matrix)
    {
        printf("[%d][%d] = %d\n", c.second.row(), c.second.col(), c.second.get_value());
    }


    return 0;
}
