#pragma once

#include "fig.h"
#include "point.h"

/**
* @brief Класс описывающий прямую на плоскости.
* Наследуется от Figure
*/
class Line : public Figure {
public:
    Line(const Point& startP, const Point& finishP, const uint32_t & id) :
            Figure(id), m_startP(startP), m_finishP(finishP) {}

    /**
    * @return Возвращает Point центра окружности.
    */
    Point get_startP() { return m_startP; }

    /**
    * @return Возвращает Point центра окружности.
    */
    Point get_finishP() { return m_finishP; }

    /**
    * @return Возвращает Point центра окружности.
    */
    std::string get_type() override { return "Line"; }

private:
    Point m_startP;
    Point m_finishP;
};