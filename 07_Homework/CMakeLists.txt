cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#configure_file(version.h.in version.h)
project(07_Homework VERSION ${PROJECT_VERSION})



add_executable(07_Homework main.cpp lib.cpp source/cmd_parser.cpp)
include_directories("include/")
target_compile_options(07_Homework PRIVATE
        -Wall -Wextra -pedantic -Werror
        )
target_compile_options(07_Homework PRIVATE
        -Wall -Wextra -pedantic -Werror
        )

install(TARGETS 07_Homework RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT n12m@bk.ru)

include(CPack)

enable_testing()

