//
// Created by murph on 04.06.23.
//

#include "Application.h"

Application::Application(int argc, char **argv) {
    m_desc.add_options()
            ("help,h", "Help Message");

    po::store(po::parse_command_line(argc, argv, m_desc), m_vm);  // парсим переданные аргументы
    po::notify(m_vm); // записываем аргументы в переменные в программе
}

int  Application::exec() {
    if (m_vm.count("help, h")){
        std::cout << m_desc << std::endl;
        return 1;
    }
    return 0;
}
