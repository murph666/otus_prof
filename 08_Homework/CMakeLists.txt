cmake_minimum_required(VERSION 3.25)
project(08_Homework)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.71.0 COMPONENTS
        filesystem
        program_options
        regex
        REQUIRED )

include_directories(${Boost_INCLUDE_DIR})
link_libraries(${Boost_LIBRARY_DIR})

if (Boost_FOUND)
    message("boost lib=> ${Boost_LIBRARIES}")
    message("boost inc=> ${Boost_INCLUDE_DIR}")
endif ()
include_directories("include/")
add_executable(08_Homework main.cpp
        source/options.cpp
        source/fs.cpp source/ds.cpp)
#        source/ds.cpp)

target_link_libraries(08_Homework Boost::filesystem
        Boost::program_options
        Boost::regex)


