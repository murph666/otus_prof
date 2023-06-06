//
// Created by murph on 04.06.23.
//

#include "Application.h"

Application::Application(int argc, char **argv) {
    m_desc.add_options()
            ("include,i", po::value<std::vector<fs::path>>(), "Include paths for scan")
            ("exclude,e", po::value<std::vector<fs::path>>(), "Exclude paths from scan")
            ("level,l", po::value<long>(), "Scan nesting level, 0 - without nested")
            ("min-size,s", po::value<long>(), "Minimum file size in bytes for scan")
            ("masks,m", po::value<std::vector<std::string>>(), "Masks for file names allowed for comparison")
            ("block-size,b", po::value<long>(), "Block size in bytes for reading file")
            ("algorithm,a", po::value<std::string>(), "Hash algorithm: crc16 or crc32")
            ("help,h", "Show help");

    po::store(po::parse_command_line(argc, argv, m_desc), m_vm);  // парсим переданные аргументы
    po::notify(m_vm); // записываем аргументы в переменные в программе
}

int Application::exec() {
    if (m_vm.count("help")) {
        std::cout << m_desc << std::endl;
        return 1;
    }

    if (m_vm.count("include")) {
        std::cout << "include" << std::endl;
    } else if (m_vm.count("level")) {
        std::cout << "level" << std::endl;
    } else if (m_vm.count("min-size")) {
        std::cout << "min-size" << std::endl;
    } else if (m_vm.count("masks")) {
        std::cout << "masks" << std::endl;
    } else if (m_vm.count("block-size")) {
        std::cout << "block-size" << std::endl;
    } else if (m_vm.count("algorithm")) {
        std::cout << "algorithm" << std::endl;
    } else if (m_vm.count("help")) {
        std::cout << m_desc << std::endl;
    } else {
        // В противном случае предлагаем посмотреть справку
        std::cout << "Please, use --help option for information" << std::endl;
        return 1;
    }


    return 0;
}
