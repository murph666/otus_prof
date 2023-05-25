//
// Created by murph on 26.05.23.
//

#ifndef INC_05_HOMEWORK_GVIEW_H
#define INC_05_HOMEWORK_GVIEW_H


class gView {
public:
    gView() = delete;
    explicit gView(const std::shared_ptr<gModel>& gmdl): graphics_model(gmdl){};

private:
    std::shared_ptr<gModel> graphics_model;

};


#endif //INC_05_HOMEWORK_GVIEW_H
