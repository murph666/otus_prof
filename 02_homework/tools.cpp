#include "tools.h"

int version()
{
    return PROJECT_VERSION_PATCH;
}

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

uint32_t strIP2uint(const std::vector<std::string> &vec)
{
    uint32_t result = 0;
    uint16_t oct1, oct2, oct3, oct4;
    oct1 = std::stoi(vec[0]);
    oct2 = std::stoi(vec[1]);
    oct3 = std::stoi(vec[2]);
    oct4 = std::stoi(vec[3]);
    result = (oct1 << 24) + (oct2 << 16) + (oct3 << 8) + oct4;
    return result;
}

std::string uint2strIP(const uint32_t &ip)
{
    std::string result = "";
    result += std::to_string((ip >> 24)) + ".";
    result += std::to_string(ip >> 16 & 0xff) + ".";
    result += std::to_string(ip >> 8 & 0xff) + ".";
    result += std::to_string(ip & 0xFF);
    return result;
}

void sort_pool(std::vector<uint32_t> &pool, int begin, int end)
{
    if (begin < end)
    {
        int mid_of_pool = begin + (end - begin) / 2;
        sort_pool(pool, begin, mid_of_pool);
        sort_pool(pool, mid_of_pool + 1, end);
        merge(pool, begin, end, mid_of_pool);
    }
}

void merge(std::vector<uint32_t> &pool, int begin, int end, int mid)
{
    int i, j, k;
    int left_pool_size = mid - begin + 1;
    int right_pool_size = end - mid;
    std::vector<uint32_t> left_pool(left_pool_size);
    std::vector<uint32_t> right_pool(right_pool_size);

    for (int i = 0; i < left_pool_size; i++)
        left_pool[i] = pool[begin + i];

    for (int j = 0; j < right_pool_size; j++)
        right_pool[j] = pool[mid + j + 1];

    auto compareIP = [](uint32_t ip1, uint32_t ip2)
    { return ip1 > ip2; };
    i = j = 0;
    k = begin;
    while (i < left_pool_size && j < right_pool_size)
    {
        if (compareIP(left_pool[i], right_pool[j]))
        {
            pool[k] = left_pool[i];
            i++;
        }
        else
        {
            pool[k] = right_pool[j];
            j++;
        }
        k++;
    }

    while (i < left_pool_size)
    {
        pool[k] = left_pool[i];
        i++;
        k++;
    }

    while (j < right_pool_size)
    {
        pool[k] = right_pool[j];
        j++;
        k++;
    }
}

std::vector<uint32_t> filterIPv4(std::vector<uint32_t> &pool, filter_mask filter)
{
    std::vector<uint32_t> filtered;
    uint16_t oct_count = 0;

    if (filter.oct1 >= 0) oct_count++;
    if (filter.oct2 >= 0) oct_count++;
    if (filter.oct3 >= 0) oct_count++;
    if (filter.oct4 >= 0) oct_count++;

    for (auto el : pool)
    {
        uint16_t count = 0;

        if ((filter.oct1 >= 0) && (static_cast<uint16_t>(el >> 24) == filter.oct1))
            count++;
        if ((filter.oct2 >= 0) && (static_cast<uint16_t>(el >> 16 & 0xff) == filter.oct2))
            count++;
        if ((filter.oct3 >= 0) && (static_cast<uint16_t>(el >> 8 & 0xff) == filter.oct3))
            count++;
        if ((filter.oct4 >= 0) && (static_cast<uint16_t>(el & 0xFF) == filter.oct4))
            count++;

        if (count == oct_count)
        {
            filtered.push_back(el);
        }
    }

    return filtered;
}

std::vector<uint32_t> filterIPv4_any(std::vector<uint32_t> &pool, const uint16_t &filter)
{
    std::vector<uint32_t> filtered;
    for (auto el : pool)
    {
        if ((el >> 24 == filter) || ((el >> 16 & 0xff) == filter) || ((el >> 8 & 0xff) == filter) || ((el & 0xFF) == filter))
            filtered.push_back(el);
    }

    return filtered;
}