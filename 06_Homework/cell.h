//
// Created by murph on 28.05.23.
//

#ifndef INC_06_HOMEWORK_CELL_H
#define INC_06_HOMEWORK_CELL_H

#include "matrix.h"

template<typename T, T default_val = 0>
class Cell{
public:
    Cell() = default;
    explicit Cell(int v){
        value(v);
    }

    void set_pos(int x, int y){m_row = x; m_col = y;}
    ~Cell() = default;
private:
    int m_row{};
    int m_col{};

    T value = default_val;
};


template<typename T, T default_val = 0>
class RowMatrix{
public:
    explicit RowMatrix(Matrix<T, default_val> &matrix, int row):
    m_matrix(matrix), m_row(row){};

    Cell<T, default_val>& operator[](int col){
        auto it = m_matrix.find(std::make_pair(m_row, col));
        if (it != m_matrix.end()){
            it.second.set_pos(m_row, col);
            return it.second;
        }
    }

private:
    Matrix<T, default_val> &m_matrix;
    int m_row;
};

#endif //INC_06_HOMEWORK_CELL_H
