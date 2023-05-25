#ifndef INC_04_HOMEWORK_GCONTROL_H
#define INC_04_HOMEWORK_GCONTROL_H

#include <cstdint>
#include <vector>
#include "point.h"
#include "fig.h"
#include "circle.h"
#include "dot.h"
#include "line.h"
#include "rectangle.h"
#include "gModel.h"
#include "gView.h"

#include "memory"

/**
* @brief Контроллер по работе с графическими объектами.
*/

class gControl {
public:
    gControl() = default;

    explicit gControl(std::shared_ptr<gModel>& gmdl) : m_graphics_model(gmdl) {
        m_graphics_view = std::make_shared<gView>(m_graphics_model);
    }

    ~gControl() = default;


    void create_dot(const Point& p1);

    void create_line(const Point& p1, const Point& p2);

    void create_circle(const Point& p1, const uint32_t& radius);

    void create_rectangle(const Point& p1, const Point& p2);

    void delete_object(const uint32_t& figure_id);

    std::shared_ptr<gView> get_view() {
        return m_graphics_view;
    }

private:
    std::shared_ptr<gView> m_graphics_view;
    std::shared_ptr<gModel> m_graphics_model;
};
#endif //INC_04_HOMEWORK_GCONTROL_H
