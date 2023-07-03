cmake_minimum_required(VERSION 3.25)
project(proj)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2 SDL2main)
find_package(OpenGL REQUIRED)

include_directories("/usr/include/SDL2")

add_subdirectory(Lolibox/vendor)
include_directories(ImageProcessor/shaders)

add_library(lolibox STATIC)
target_include_directories(lolibox PUBLIC Lolibox/src)
target_sources(lolibox PRIVATE
        Lolibox/src/Lolibox.h
        Lolibox/src/Lolibox/Application.cpp
        Lolibox/src/Lolibox/Logger.cpp
        Lolibox/src/Lolibox/Window.cpp
        Lolibox/src/Lolibox/Events/Event.cpp
        Lolibox/src/Lolibox/Events/EventBus.cpp
        Lolibox/src/Lolibox/Events/WindowEvents.cpp
        Lolibox/src/Lolibox/Graphics/ComputeShader.cpp
        Lolibox/src/Lolibox/Graphics/Framebuffer.cpp
        Lolibox/src/Lolibox/Graphics/FramebufferShader.cpp
        Lolibox/src/Lolibox/Graphics/Mesh.cpp
        Lolibox/src/Lolibox/Graphics/RenderModule.cpp
        Lolibox/src/Lolibox/Graphics/Shader.cpp
        Lolibox/src/Lolibox/Graphics/Texture.cpp
        Lolibox/src/Lolibox/Graphics/Uniforms/FloatUniform.cpp
        Lolibox/src/Lolibox/Graphics/Uniforms/Int1Uniform.cpp
        Lolibox/src/Lolibox/Graphics/Uniforms/Mat3Uniform.cpp
        Lolibox/src/Lolibox/Graphics/Uniforms/ShaderUniform.cpp
        Lolibox/src/Lolibox/Graphics/Uniforms/TextureUniform.cpp
        Lolibox/src/Lolibox/Graphics/Uniforms/Vec2fUniform.cpp
        Lolibox/src/Lolibox/Graphics/Uniforms/Vec3fUniform.cpp
        Lolibox/src/Lolibox/UI/NativeMessages.cpp
        Lolibox/src/Lolibox/UI/UIBase.cpp
        Lolibox/src/Lolibox/Utility/FileSystem.cpp
        Lolibox/src/Lolibox/Utility/Time.cpp
        Lolibox/src/Lolibox/Utility/Impl/stb_image.cpp
        Lolibox/src/Lolibox/Utility/Impl/stb_image_write.cpp

        )

target_link_libraries(lolibox PUBLIC
        SDL2
        SDL2main
        glad
        glm
        eventpp
        imgui
        nfd # Native File Dialog Extended
        stb)

target_precompile_headers(lolibox PUBLIC
        Lolibox/src/pch.h)


add_executable(image-processor)
target_include_directories(image-processor PRIVATE ImageProcessor/src)
target_sources(image-processor PRIVATE
        ImageProcessor/src/App.cpp
        ImageProcessor/src/ImageRenderer.cpp
        ImageProcessor/src/PingPong.cpp
        ImageProcessor/src/Filters/EdgeDetectFilter.cpp
        ImageProcessor/src/Filters/Filter.cpp
        ImageProcessor/src/Filters/GammaCorrectionFilter.cpp
        ImageProcessor/src/Filters/GrayscaleFilter.cpp
        ImageProcessor/src/Filters/HistogramFilter.cpp
        ImageProcessor/src/Filters/MorphFilter.cpp
        ImageProcessor/src/Filters/NegativeFilter.cpp
        ImageProcessor/src/Filters/SharpenFilter.cpp
        ImageProcessor/src/Filters/SmoothingFilter.cpp
        ImageProcessor/src/Filters/ThresholdingFilter.cpp
        )

target_link_libraries(image-processor PRIVATE lolibox)
