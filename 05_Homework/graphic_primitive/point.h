#pragma once

/**
* @brief Базовый класс для графических примитовов (точка)
*/

class Point {
public:
    Point() : m_x(0), m_y(0) {}

    explicit Point(int x, int y) : m_x(x), m_y(y) {}

    Point(const Point& point) : m_x(point.m_x), m_y(point.m_y) {}


    /**
    * @return Устанавливает x координату Point.
    */
    void set_x(int x) { m_x = x; }
    /**
    * @return Устанавливает y координату Point.
    */
    void set_y(int y) { m_y = y; }
    /**
    * @return Возвращает x координату Point.
    */
    int get_x() { return m_x; }
    /**
    * @return Возвращает y координату Point.
    */
    int get_y() { return m_y; }

private:
    int m_x;
    int m_y;
};