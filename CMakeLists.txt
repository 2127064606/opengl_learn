cmake_minimum_required(VERSION 3.10)
project(opengl_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLAD_SRC C:/glad/src/)
# -------------------------- 手动指定GLFW路径 --------------------------
# GLFW头文件路径（指向包含GLFW目录的上级）
include_directories("C:/glfw-3.4.bin.WIN64/glfw-3.4.bin.WIN64/include")
include_directories("C:/glad/include")
include_directories("C:/glm-0.9.8.5/glm")
# GLFW库文件路径（指向存放.lib或.a的目录，根据实际子目录调整）
# 例如：如果库在C:\glfw-3.4\glfw-3.4\lib-mingw-w64，则改为下面的路径
link_directories("C:/glfw-3.4.bin.WIN64/glfw-3.4.bin.WIN64/lib-vc2022")  # 替换为你的库目录
add_subdirectory(tools)
enable_testing(test)
add_subdirectory(test)
# -------------------------- 其他库置（如GLAD、GLM） --------------------------
# 如果GLAD也是手动放置的，类似指定路径（例如GLAD放在项目的vendor目录下）
# include_directories("vendor/glad/include")  # 假设GLAD头文件路径
# add_library(glad STATIC vendor/glad/src/glad.c)  # 编译GLAD源码

# 如果GLM手动安装，同样指定头文件路径
# include_directories("C:/path/to/glm/include")

# -------------------------- 生成可执行文件 --------------------------
add_executable(${PROJECT_NAME} main.cpp ${GLAD_SRC}/glad.c)  # 若有GLAD源码，需加入：vendor/glad/src/glad.c

# -------------------------- 链接库 --------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
  glfw3  # 链接GLFW库（根据库文件名称调整，如libglfw3.a则写glfw3）
  ToolLib  # 链接Tool库
)

# 链接系统OpenGL库（Windows默认是opengl32.lib）
if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE GL)
elseif(APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()