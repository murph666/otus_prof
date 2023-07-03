add_library(glad OBJECT) #OBJECT - не будет создаваться отдельно файлик библиотеки!
target_include_directories(glad PUBLIC glad/include)
target_sources(glad PRIVATE glad/src/glad.c)
target_compile_definitions(glad PUBLIC _GLAD_X11) #Определяем что использовать для glada (иксы под линукс)
target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS})


add_subdirectory(glm)

add_subdirectory(nfd)

add_subdirectory(eventpp)


add_library(imgui OBJECT) #OBJECT - не будет создаваться отдельно файлик библиотеки!
target_include_directories(imgui PUBLIC
        imgui imgui/backends
        imgui/examples)
target_sources(imgui PRIVATE
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_sdl2.cpp
        imgui/backends/imgui_impl_opengl3.cpp)
target_compile_definitions(imgui PUBLIC
        IMGUI_IMPL_OPENGL_LOADER_GLAD
        _IMGUI_X11)
target_link_libraries(imgui PUBLIC SDL2 glad)


add_library(stb INTERFACE)
target_include_directories(stb INTERFACE stb)
