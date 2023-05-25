//
// Created by murph on 26.05.23.
//

#ifndef INC_05_HOMEWORK_DVIEW_H
#define INC_05_HOMEWORK_DVIEW_H
#include "dModel.h"

class dView {

public:
    dView() = delete;

    explicit dView(const std::shared_ptr <dModel> &dmdl) : doc_model(dmdl) {};

private:
    std::shared_ptr <dModel> doc_model;


};


#endif //INC_05_HOMEWORK_DVIEW_H
