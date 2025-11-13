add_library(
    test_tools
    MyCamera.hpp
    MyCamera.cpp
    MyShader.hpp
    MyShader.cpp
    MyMesh.hpp
    MyMesh.cpp
    MyModel.hpp
    MyModel.cpp
    Info.hpp
    ObjectDef.hpp
)

target_link_libraries(test_tools PRIVATE ToolLib)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_features(test_tools PRIVATE cxx_std_17)

target_include_directories(test_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
