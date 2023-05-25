#pragma once

#include "fig.h"
#include "point.h"

/**
* @brief Класс описывающий прямоугольник.
* Наследуется от Figure
*/
class Rectangle : public Figure {
public:
    Rectangle() = default;
    explicit Rectangle(const Point& upperLeftP , const Point& bottomRightP, const uint32_t & id) :
            Figure(id), m_upperLeftP(upperLeftP), m_bottomRightP(bottomRightP) {}
    ~Rectangle() = default;

    /**
    * @return Вовзращает левый верхний Point прямоугольника.
    */
    Point get_upperLeftP() { return m_upperLeftP; }

    /**
    * @return Вовзращает правый нижный Point прямоугольника.
    */
    Point get_bottomRightP() { return m_bottomRightP; }

    /**
    * @return Возвращает тип графического примитива.
    */
    std::string get_type() override { return "Rectangle"; }

private:
    Point m_upperLeftP;
    Point m_bottomRightP;
};