//
// Created by murph on 22.04.23.
//
#ifndef INC_06_HOMEWORK_MATRIX_H
#define INC_06_HOMEWORK_MATRIX_H

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
class Cell;

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

    void insert(const coord &pos, Cell<T, default_val> *cell) {
        m_matrix.insert(std::make_pair(pos, *cell));
    }

    size_t size() { return m_matrix.size(); }

private:
    matrix_t m_matrix;

};

template<typename T, int default_val>
class RowMatrix{
public:
    explicit RowMatrix(Matrix<T, default_val> &matrix, int row):
            m_matrix(matrix),m_newCell(Cell<T, default_val>(matrix, default_val)), m_row(row){};

    Cell<T, default_val>& operator[](int col){
        auto it = m_matrix.find(std::make_pair(m_row, col));
        if (it != m_matrix.end()){
            it->second.set_pos(m_row, col);
            return it->second;
        }
        else{
            m_newCell.set_pos(m_row, col);
            return m_newCell;
        }

    };

private:
    Matrix<T, default_val> &m_matrix;
    Cell<T, default_val> m_newCell;
    int m_row;
};

template<typename T, int default_val>
class Cell{
public:
    Cell() = default;

    explicit Cell(Matrix<T, default_val> &matrix, int v):
        m_matrix(matrix), m_value(v){

    }
    ~Cell() = default;

    T get_value() {
        return m_value;
    }
    T row() {
        return m_row;
    }
    T col() {
        return m_col;
    }


    void operator=(int const& value) {
        coord position = std::make_pair(m_row, m_col);

        if (value == default_val) {
            auto it = m_matrix.find(position);
            if (it != m_matrix.end()) {
                m_matrix.erase(it);
            }
        }
        else {
            m_value = value;
            m_matrix.insert(position, this);
        }


    }

    void set_pos(int x, int y){m_row = x; m_col = y;}


    friend bool operator==(Cell<T, default_val>& lhs, T const& rhs) {
        return lhs.get_value() == rhs;
    }

    friend std::ostream& operator<<(std::ostream& os, Cell<T, default_val> const& obj) {
        os << ((obj.m_value == default_val) ? default_val : obj.m_value);
        return os;
    }

private:
    int m_row = 0;
    int m_col = 0;
    Matrix<T, default_val> &m_matrix;
    T m_value = default_val;
};

#endif