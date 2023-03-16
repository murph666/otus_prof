#include "one_way_list_container.hpp"
#include "test_allocator.hpp"
#include <unistd.h>  
#include <iostream>

int main()
{
	std::cout << "PID процесса: " << getpid() << std::endl;
	test_map_std_allocator();
	test_map_allocator();
	test_container_std_allocator();
	test_container_allocator();
	return 0;
}
