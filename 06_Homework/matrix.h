//
// Created by murph on 22.04.23.
//
#ifndef INC_06_HOMEWORK_MATRIX_H
#define INC_06_HOMEWORK_MATRIX_H

#include "cell.h"
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#define UNUSED(x) (void)x;
using coord = std::pair<int, int>;

template<typename T, int default_val = 0>
class RowMatrix;

template<typename T, int default_val = 0>
class Matrix {
    using matrix_t = typename std::map<coord, Cell<T, default_val>>;
    using matrix_iter = typename std::map<coord, Cell<T, default_val>>::iterator;
public:
    Matrix() = default;
    ~Matrix() = default;

    RowMatrix<T, default_val> operator[](int row){
        return RowMatrix<T, default_val>(*this, row);
    }

    matrix_t get_matrix() { return m_matrix; }

    matrix_iter begin() { return m_matrix.begin(); }
    matrix_iter end() { return m_matrix.end(); }
    matrix_iter find(const coord &pos) { return m_matrix.find(pos); }
    matrix_iter erase(const matrix_iter &iter) { return m_matrix.erase(iter); }

    void insert(const coord &pos, const Cell<T, default_val> &cell) {
        m_matrix.insert(std::make_pair(pos, cell));
    }

    size_t size() { return m_matrix.size(); }

private:
    matrix_t m_matrix;

};

template<typename T, int default_val>
class RowMatrix{
public:
    explicit RowMatrix(Matrix<T, default_val> &matrix, int row):
            m_matrix(matrix), m_row(row){};

    Cell<T, default_val>& operator[](int col){
        auto it = m_matrix.find(std::make_pair(m_row, col));
        if (it != m_matrix.end()){
            it->second.set_pos(m_row, col);

        }
        return it->second;
    };

private:
    Matrix<T, default_val> &m_matrix;
    int m_row;
};
#endif