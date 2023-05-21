//
// Created by murph on 14.05.23.
//

#ifndef INC_05_HOMEWORK_GMODEL_H
#define INC_05_HOMEWORK_GMODEL_H
#include <cstdint>
#include <vector>
#include <memory>

#include "fig.h"

class gModel {
public:
    gModel(): m_width(10), m_height(10), m_last_number(0){}
    explicit gModel(const uint32_t &w, const uint32_t &h):
        m_width(w), m_height(h), m_last_number(0){}

    ~gModel() = default;

    void add_figure(std::shared_ptr<Figure> &fig_id);
    void del_figure(uint32_t &fig_id);
    void clear_model(){m_figure.clear();};

    std::vector<std::shared_ptr<Figure>> get_graphic_objects() {return m_figure;}

    uint32_t get_last_id() { return m_last_number;}

    void resize_scene(const uint32_t& w, const uint32_t& h) {
        m_width = w;
        m_height = h;
    }

private:
    std::vector<std::shared_ptr<Figure>> m_figure;

    //Ширина и высота графической области.
    uint32_t m_width;
    uint32_t m_height;

    uint32_t m_last_number;
};


#endif //INC_05_HOMEWORK_GMODEL_H
