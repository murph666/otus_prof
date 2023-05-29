//
// Created by murph on 23.05.23.
//
#ifndef INC_06_HOMEWORK_CELL_H
#define INC_06_HOMEWORK_CELL_H

#include "matrix.h"

using coord = std::pair<int, int>;

template<typename T, int default_val = 0>
class Cell{
public:
    Cell() = default;
    explicit Cell(int v){
        m_value(v);
    }

    T get_value() {
        return m_value;
    }

    Cell& operator=(int const& value) {
        coord position = std::make_pair(m_row, m_col);

        if (value == default_value) {
            auto it = matrix.find(position);

            if (it != matrix.end()) {
                matrix.erase(it);
            }
        }
        else {
            matrix.insert(position, CellValue(matrix, value));
        }

        return *this;
    }

    void set_pos(int x, int y){m_row = x; m_col = y;}
    ~Cell() = default;
private:
    int m_row{};
    int m_col{};

    T m_value = default_val;
};
#endif //INC_06_HOMEWORK_CELL_H
