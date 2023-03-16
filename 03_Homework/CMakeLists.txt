cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(03_Homework
  VERSION ${PROJECT_VESRION}
  LANGUAGES CXX)

configure_file(version.h.in version.h)

add_executable(main main.cpp one_way_list_container.hpp allocator.hpp)
add_library(test_allocator test_allocator.cpp)


set_target_properties(main test_allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(test_allocator
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_link_libraries(main PRIVATE
test_allocator
)
target_compile_options(main PRIVATE
-Wall -Wextra -pedantic -Werror
)
target_compile_options(test_allocator PRIVATE
-Wall -Wextra -pedantic -Werror
)

install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT n12m@bk.ru)

include(CPack)

enable_testing()
