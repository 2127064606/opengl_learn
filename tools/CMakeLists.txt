add_library(
    ToolLib
    Shader.hpp
    Shader.cpp
    Camera.hpp
    Camera.cpp
    stb_image.h
    stb_image.cpp
    Mesh.hpp
    Mesh.cpp
    Model.hpp
    Model.cpp
)

include_directories("C:/glad/include")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 C++ 标准
target_compile_features(ToolLib PRIVATE cxx_std_17)

# 确保包含目录正确设置
target_include_directories(ToolLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

