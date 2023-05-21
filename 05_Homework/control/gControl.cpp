//
// Created by murph on 14.05.23.
//
#include "gControl.h"

void gController::create_dot(const Point &p1) {
    auto last_id = m_graphics_model.get_last_id();
    std::shared_ptr<Figure> new_dot = std::make_shared<Dot>(p1, last_id);
    m_graphics_model.add_figure(new_dot);
}
void gController::create_line(const Point &p1, const Point &p2) {
    auto last_id = m_graphics_model.get_last_id();
    std::shared_ptr<Figure> new_line = std::make_shared<Line>(p1,p2,last_id);
    m_graphics_model.add_figure(new_line);
}

void gController::create_circle(const Point &p1, const uint32_t &radius) {
    auto last_id = m_graphics_model.get_last_id();
    std::shared_ptr<Figure> new_dot = std::make_shared<Dot>(p1, last_id);
    m_graphics_model.add_figure(new_dot);
}

void gController::create_rectangle(const Point &p1, const Point &p2) {
    auto last_id = m_graphics_model.get_last_id();
    std::shared_ptr<Figure> new_dot = std::make_shared<Dot>(p1, last_id);
    m_graphics_model.add_figure(new_dot);
}

void gController::delete_object(const uint32_t &figure_id) {
    auto last_id = m_graphics_model.get_last_id();
    std::shared_ptr<Figure> new_dot = std::make_shared<Dot>(p1, last_id);
    m_graphics_model.add_figure(new_dot);
}

