#include "test_allocator.hpp"
#include "logging_allocator.cpp"
#include "allocator.hpp"
#include "one_way_list_container.hpp"
#include <map>
#include <iostream>

int factorial(const int n)
{
    return (n < 2 ? 1 : n * factorial(n - 1));
}

void test_map_std_allocator()
{
    std::cout << "test_map_std_allocator" << std::endl;

    std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>>> test_map_std_allocator;
    for (int i = 0; i < 7; ++i)
    {
        test_map_std_allocator[i] = factorial(i);
    }

    for (const auto &[key, value] : test_map_std_allocator)
        std::cout << '[' << key << "] = " << value << "; \t\t" << &key << ":" << &value << std::endl;
    

    std::cout << sizeof(test_map_std_allocator)<< std::endl;
    std::cout << std::endl;
}

void test_map_allocator()
{
    std::cout << "test_map_allocator" << std::endl;
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>> test_map_allocator;
    for (int i = 0; i < 7; ++i)
    {
        test_map_allocator[i] = factorial(i);
    }

    for (const auto &[key, value] : test_map_allocator)
        std::cout << '[' << key << "] = " << value << "; \t" << &key << ":" << &value << std::endl;;
    std::cout << sizeof(test_map_allocator)<< std::endl;
    std::cout << std::endl;
}
void test_container_allocator()
{
    std::cout << "test_container_allocator" << std::endl;
    // OneWayList<int, logging_allocator<int>> OneWayList_container;
    OneWayList<int, CustomAllocator<int, 1>> OneWayList_container;
	for (int i = 0; i < 10; ++i)
	{
		OneWayList_container.push_back(factorial(i));
	}
    std::cout << OneWayList_container << std::endl;
    std::cout << std::endl;
}
void test_container_std_allocator()
{
    std::cout << "test_container_std_allocator" << std::endl;
    OneWayList<int> OneWayList_def_container;
	for (int i = 0; i < 6; ++i)
	{
		OneWayList_def_container.push_back(factorial(i));
	}
    
    std::cout << OneWayList_def_container << std::endl;
    std::cout << std::endl;
}