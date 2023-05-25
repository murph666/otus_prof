#pragma once

#include <string>
#include "fig.h"
#include "point.h"

/**
* @brief Класс описывающий окружность.
* Наследуется от Figure
*/

class Circle: public Figure{
public:
    Circle(const Point& center, const uint32_t& radius, const uint32_t &id) :
            Figure(id), radius(radius), center(center) {}
    ~Circle() = default;

    /**
    * @return Возвращает Point центра окружности.
    */
    Point get_center() { return center; }

    /**
    * @return Возвращает радиус окружности.
    */
    uint32_t get_radius() { return radius; }

    /**
    * @return Возвращает тип графического примитива.
    */
    std::string get_type() override { return "Circle"; }



private:
    uint32_t    radius;
    Point       center;
};