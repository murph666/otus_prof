#pragma once
#include <vector>
#include <string>
#include <iostream>

struct filter_mask{
    int16_t oct1 = -1;
    int16_t oct2 = -1;
    int16_t oct3 = -1;
    int16_t oct4 = -1;
};

int version();
std::vector<std::string> split(const std::string &str, char d);
uint32_t strIP2uint(const std::vector<std::string> &vec);
std::string uint2strIP(const uint32_t &ip);
void sort_pool(std::vector<uint32_t> &pool, int begin, int end);
void merge(std::vector<uint32_t> &pool, int begin, int end, int mid);
std::vector<uint32_t> filterIPv4(std::vector<uint32_t> &pool, filter_mask filter);
std::vector<uint32_t> filterIPv4_any(std::vector<uint32_t> &pool, const uint16_t& filter);