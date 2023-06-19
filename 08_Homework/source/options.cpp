#include "options.h"

#include <iostream>
#include <exception>


OptionsParser::OptionsParser()
        : m_desc("Options") {
    m_desc.add_options()
            ("include,i", boost::program_options::value<std::vector<boost::filesystem::path>>(), "Include paths for scaning")
            ("exclude,e", boost::program_options::value<std::vector<boost::filesystem::path>>(), "Exclude paths from scaning")
            ("level,l", boost::program_options::value<long>(), "Scan nesting level, 0 - without nested")
            ("min-size,s", boost::program_options::value<long>(), "Minimum file size in bytes for scaning")
            ("masks,m", boost::program_options::value<std::vector<std::string>>(), "Masks for file names allowed for comparison")
            ("block-size,b", boost::program_options::value<long>(), "Block size in bytes for reading file")
            ("algorithm,a", boost::program_options::value<std::string>(), "Hash algorithm: crc16 or crc32")
            ("help,h", "Show help");
}

OptionsParser::OptionsResult OptionsParser::GetOptions(int argc, char **argv) {
    std::cout << "argc: " << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }

    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, m_desc), m_var);
        boost::program_options::notify(m_var);

        if (m_var.count("help")) {
            std::cout << m_desc << "\n";
            return {};
        }

        Options options;

        if (m_var.count("include")) {
            options.includePaths = m_var["include"].as<std::vector<boost::filesystem::path>>();
            for (auto &path: options.includePaths) {
                if (path.is_relative()) {
                    path = boost::filesystem::canonical(path);
                }
            }
        }

        if (m_var.count("exclude")) {
            options.excludePaths = m_var["exclude"].as<std::vector<boost::filesystem::path>>();
            for (auto &path: options.excludePaths) {
                if (path.is_relative()) {
                    path = boost::filesystem::canonical(path);
                }
            }
        }

        if (m_var.count("level")) {
            long nLevel = m_var["level"].as<long>();
            options.levelScan = static_cast<std::size_t>(nLevel);
        }

        if (m_var.count("min-size")) {
            long nMinSize = m_var["min-size"].as<long>();
            options.minFileSize = static_cast<std::size_t>(nMinSize);
        }

        if (m_var.count("masks")) {
            options.masks = m_var["masks"].as<std::vector<std::string>>();
        }

        if (m_var.count("block-size")) {
            long nBlockSize = m_var["block-size"].as<long>();
            options.blockSize = static_cast<std::size_t>(nBlockSize);
        }

        if (m_var.count("algorithm")) {
            std::string strHash = m_var["algorithm"].as<std::string>();
            options.hash = strHash;
        }

        return options;
    }
    catch (std::exception &ex) {
        std::cout << "Error: " << ex.what() << std::endl << std::endl;
        std::cout << m_desc << std::endl;
        return {};
    }
}

