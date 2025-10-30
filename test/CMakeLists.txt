add_executable(test_main test_main.cpp ${GLAD_SRC}/glad.c)

add_executable(test_sun test_sun.cpp ${GLAD_SRC}/glad.c)
add_test(test_main test_main)
add_test(test_sun test_sun)

target_link_libraries(test_main PRIVATE glfw3 ToolLib)
target_link_libraries(test_sun PRIVATE glfw3 ToolLib)
