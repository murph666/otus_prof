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

#include "memory"

/**
* @brief Контроллер по работе с графическими объектами.
*/

class gController {
public:
    gController() = default;

    explicit gController(const std::shared_ptr<gModel>& gr_mdl) : m_graphics_model(gr_mdl) {
        // Ñîçäàåì View è ïåðåäàåì åé óêàçàòåëü íà ìîäåëü ñ ãðàôèêîé.
        graphics_view = std::make_shared<GraphicsView>(graphics_model);

        // Ó ìîäåëè óêàçûâàåì View êàê îáîçðåâàòåëü.
        m_graphics_model->attach(graphics_view);
    }

    ~GraphicsController() {
        graphics_model->detach(graphics_view);
    }


    void create_dot(const Point& p1);

    void create_line(const Point& p1, const Point& p2);

    void create_circle(const Point& p1, const uint32_t& radius);

    void create_rectangle(const Point& p1, const Point& p2);

    void delete_object(const uint32_t& figure_id);

private:
    std::shared_ptr<GraphicsView> graphics_view;
    std::shared_ptr<gModel> m_graphics_model;
};
#endif //INC_04_HOMEWORK_GCONTROL_H
