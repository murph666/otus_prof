#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include "tools.h"

int main()
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

    short num = 0;

    for (const auto &entry : std::filesystem::directory_iterator(".."))
    {
        std::string filename = entry.path().filename();
        std::string extension = filename.substr(filename.rfind(".") + 1);
        if (extension == "tsv")
        {
            fileboard.insert(std::pair<int, std::string>(num, filename));
            num++;
        }
    }

    std::cout << "List of files: " << std::endl;
    for (const auto &v : fileboard)
        std::cout << v.first << ". " << v.second << std::endl;

    int f;
    std::cout << "Enter the file number: ";
    std::cin >> f;
    file = std::ifstream("../" + fileboard.at(f));

    std::string line;
    std::vector<uint32_t> ip_pool;
    
    if (file.is_open())
    {
        for (std::string line; std::getline(file, line);)
        {
            std::vector<std::string> v = split(split(line, '\t').at(0), '.');
            uint32_t i = strIP2uint(v);
            ip_pool.push_back(i);
        }

        file.close();
    }

    sort_pool(ip_pool, 0, ip_pool.size() - 1);

    for (auto el : ip_pool)
        std::cout << uint2strIP(el) << std::endl;

    filter_mask mask;
    std::vector<uint32_t> ip_sorted_pool_task1;
    mask.oct1 = 1;
    ip_sorted_pool_task1 = filterIPv4(ip_pool, mask);
    if (!ip_sorted_pool_task1.empty())
        for (auto el : ip_sorted_pool_task1)
            std::cout << uint2strIP(el) << std::endl;
    else
        std::cout << "Empty :(" << std::endl;

    std::vector<uint32_t> ip_sorted_pool_task2;
    mask.oct1 = 46;
    mask.oct2 = 70;
    ip_sorted_pool_task2 = filterIPv4(ip_pool, mask);
    if (!ip_sorted_pool_task2.empty())
        for (auto el : ip_sorted_pool_task2)
            std::cout << uint2strIP(el) << std::endl;
    else
        std::cout << "Empty :(" << std::endl;

    std::vector<uint32_t> ip_sorted_pool_task3;

    ip_sorted_pool_task3 = filterIPv4_any(ip_pool, 46);
    if (!ip_sorted_pool_task3.empty())
        for (auto el : ip_sorted_pool_task3)
            std::cout << uint2strIP(el) << std::endl;
    else
        std::cout << "Empty :(" << std::endl;

    return 0;
}