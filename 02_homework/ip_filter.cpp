#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <dirent.h>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{
    char cwd[1024];
    std::map<int, std::string> fileboard;
    std::ifstream file;

    if (getcwd(cwd, 1024) != NULL)
    {
        std::cout << "Current working directory: " << cwd << std::endl;
    }
    else
    {
        std::cout << "Error getting current directory!" << std::endl;
    }

    if (argc == 1)
    {
        DIR *dirp;
        struct dirent *dp;
        struct stat info;
        short num = 0;

        dirp = opendir(cwd);

        while ((dp = readdir(dirp)) != NULL)
        {
            if (stat(dp->d_name, &info) == 0 && !S_ISDIR(info.st_mode))
            {
                std::string filename = dp->d_name;
                std::string extension = filename.substr(filename.rfind(".") + 1);
                if (extension == "tsv")
                {
                    fileboard.insert(std::pair<int, std::string>(num, dp->d_name));
                    num++;
                }
            }
        }
        closedir(dirp);

        std::cout << "List of files: " << std::endl;
        for (const auto &v : fileboard)
            std::cout << v.first << ". " << v.second << std::endl;

        int f;
        std::cout << "Enter the file number: ";
        std::cin >> f;
        file = std::ifstream(fileboard.at(f));
    }
    else if (argc == 2)
    {
        std::string filename = argv[1];
        std::string extension = filename.substr(filename.rfind(".") + 1);
        if (extension == "tsv") file = std::ifstream(filename);
        else std::cout << "Invalid file format";
    }
    else
    {
        std::cout << "Invalid command";
    }

    std::string line;
    std::vector<std::vector<std::string>> ip_pool;
    if (file.is_open())
    {
        for (std::string line; std::getline(file, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        file.close();
    }
    return 0;
}