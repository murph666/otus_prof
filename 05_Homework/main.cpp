//
// Created by murph on 09.05.23.
//

#include "lib.h"

#include "gControl.h"
#include "dControl.h"
#include "dModel.h"
#include "gModel.h"


/**
 * @file main.cpp
 *
 * Simple vector graphcs editor.
 */

int main (int, char **) {

    std::shared_ptr<gModel>  graphics_model  = std::make_shared<gModel>(200, 200);
    std::shared_ptr<dModel> documents_model = std::make_shared<dModel>(graphics_model);

    std::shared_ptr<gControl> graphics_controller  = std::make_shared<gControl>(graphics_model);
    std::shared_ptr<dControl> documents_controller = std::make_shared<dControl>(documents_model);

    auto graphics_view  = graphics_controller->get_view();
    auto documents_view = documents_controller->get_view();

    documents_controller->create_document();

    graphics_controller->create_dot( Point(5, 5) );
    graphics_controller->create_line( Point(5, 3), Point(2, 1) );
    graphics_controller->create_circle( Point(12, 3), 10 );
    graphics_controller->create_rectangle( Point(2, 3), Point(41, 8) );

    return 0;
}