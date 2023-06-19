//
// Created by murph on 17.06.23.
//

#ifndef INC_08_HOMEWORK_OPTIONS_H
#define INC_08_HOMEWORK_OPTIONS_H
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/optional.hpp>

struct Options
{
    std::vector<boost::filesystem::path>    includePaths;
    std::vector<boost::filesystem::path>    excludePaths;
    boost::optional<std::size_t>            levelScan;
    boost::optional<std::size_t>            minFileSize;
    std::vector<std::string>                masks;
    boost::optional<std::size_t>            blockSize;
    boost::optional<std::string>            hash;
};

class OptionsParser
{
public:
    OptionsParser();

    using OptionsResult = boost::optional<Options>;

    OptionsResult GetOptions(int argc, char** argv);

private:
    boost::program_options::options_description m_desc;
    boost::program_options::variables_map m_var;
};

#endif //INC_08_HOMEWORK_OPTIONS_H
