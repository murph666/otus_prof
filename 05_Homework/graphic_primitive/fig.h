#pragma once

#include <string>

/**
* @brief Базовый класс для графических примитовов (фигура).
*/

class Figure {
public:
    Figure() : figure_id(0) {}

    Figure(const uint32_t& id) : figure_id(id) {}

    /**
    * @return Получить id примитива.
    */
    uint32_t get_id() { return figure_id; }

    /**
    * @return Получить тип примитива.
    */
    virtual std::string get_type() = 0;


private:
    uint32_t figure_id; // id примитива.
};