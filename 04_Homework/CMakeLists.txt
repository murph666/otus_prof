cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(04_Homework
        VERSION ${PROJECT_VESRION}
        LANGUAGES CXX)

configure_file(version.h.in version.h)

add_executable(04_Homework main.cpp ip_template.h)

target_compile_options(04_Homework PRIVATE
        -Wall -Wextra -pedantic -Werror
        )
target_compile_options(04_Homework PRIVATE
        -Wall -Wextra -pedantic -Werror
        )


install(TARGETS 04_Homework RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT n12m@bk.ru)

include(CPack)

enable_testing()

