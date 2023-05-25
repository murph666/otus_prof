cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(05_Homework
        VERSION ${PROJECT_VERSION}
        LANGUAGES CXX)


configure_file(version.h.in version.h)

set(SOURCES main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/control/gControl.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/models/gModel.h
                        ${CMAKE_CURRENT_SOURCE_DIR}/models/dModel.h
                        ${CMAKE_CURRENT_SOURCE_DIR}/doc/doc.h)
add_executable(hm_exec ${SOURCES})
add_library(lib_mvc lib.cpp)

target_include_directories(hm_exec PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/control
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/models
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/graphic_primitive
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/doc)

target_compile_options(hm_exec PRIVATE
        -Wall -Wextra -pedantic -Werror
        )
target_compile_options(hm_exec PRIVATE
        -Wall -Wextra -pedantic -Werror
        )

target_link_libraries(hm_exec PRIVATE
        lib_mvc
        )


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT n12m@bk.ru)

include(CPack)

enable_testing()

