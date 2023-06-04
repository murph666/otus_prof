//
// Created by murph on 04.06.23.
//

#ifndef INC_08_HOMEWORK_APPLICATION_H
#define INC_08_HOMEWORK_APPLICATION_H

#include "iostream"
#include <filesystem>
#include "boost/program_options.hpp"

namespace fs = std::filesystem;
namespace po = boost::program_options;

class Application {
public:
    explicit Application(int argc, char* argv[]);

    int exec();
private:
    // Описание доступных опций меню
    po::options_description m_desc {"Allowed options"};
    // контейнер для сохранения выбранных опций программы
    po::variables_map m_vm;
    // Требуемые в программе переменные для работы с опциями меню
    size_t m_blockSize = 0;
    fs::path m_inputFilePath;
    fs::path m_outputFilePath;
};


#endif //INC_08_HOMEWORK_APPLICATION_H
