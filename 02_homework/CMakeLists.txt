cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(02_Homework
  VERSION ${PROJECT_VESRION}
  LANGUAGES CXX)

configure_file(version.h.in version.h)

add_executable(ip_filter ip_filter.cpp)
add_library(tools tools.cpp tools.h)
target_link_libraries(ip_filter PRIVATE tools)

set_target_properties(ip_filter tools PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_link_libraries(ip_filter PRIVATE
    tools
)

target_compile_options(ip_filter PRIVATE
-Wall -Wextra -pedantic -Werror
)
target_compile_options(tools PRIVATE
-Wall -Wextra -pedantic -Werror
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT n12m@bk.ru)

include(CPack)

enable_testing()