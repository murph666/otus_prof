//
// Created by murph on 22.04.23.
//
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include "cell.h"

#define UNUSED(x) (void)x;
//using coord = std::pair<int, int>;
using coord = std::pair<int, int>;

template<typename T, T default_val = 0>
class Matrix {
public:
    using matrix_t = std::map<coord, Cell<T, default_val>>;
    using matrix_iter = typename std::map<coord, Cell<T, default_val>>::iterator;
    Matrix() = default;

    ~Matrix() = default;

    Cell<T, default_val> operator[](int row){
        return  RowMatrix<T, default_val>(this, row);
    };

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