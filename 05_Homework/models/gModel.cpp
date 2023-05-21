//
// Created by murph on 14.05.23.
//
#include "gModel.h"

void gModel::add_figure(std::shared_ptr<Figure> &fig_id){
    m_figure.push_back(fig_id);
    m_last_number++;
}
void gModel::del_figure(uint32_t &fig_id){
    for (auto iter = m_figure.begin(); iter != m_figure.end(); iter++){
        if ((*iter)->get_id() == fig_id){
            m_figure.erase(iter);
            break;
        }
    }
}