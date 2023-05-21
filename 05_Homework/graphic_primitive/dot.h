#pragma once

#include "fig.h"
#include "point.h"

/**
* @brief Класс описывающий точку на графической области.
* Наследуется от Figure
*/


class Dot : public Figure {
public:
    Dot(int x, int y, const uint32_t & id) : Figure(id), m_position( Point( x, y )) {}

    explicit Dot(const Point& p, const uint32_t& id) : Figure(id), m_position(p) {}

    /**
    * @return Возвращает Point точки.
    */
    Point get_position() { return m_position; }

    /**
    * @return Возвращает тип графического примитива.
    */
    std::string get_type() override { return "Dot"; }

private:
    Point m_position;
};