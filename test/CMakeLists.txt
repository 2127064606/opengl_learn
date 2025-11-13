add_executable(test_main test_main.cpp ${GLAD_SRC}/glad.c)

add_executable(test_sun test_sun.cpp ${GLAD_SRC}/glad.c)
add_executable(test_assimp test_assimp.cpp ${GLAD_SRC}/glad.c)
add_executable(test_assimp_before test_assimp_before.cpp ${GLAD_SRC}/glad.c)
add_test(test_main test_main)
add_test(test_sun test_sun)
add_test(test_assimp test_assimp)

add_test(test_assimp_before test_assimp_before)



# 在根CMakeLists.txt或test目录的CMakeLists.txt中添加
add_custom_command(TARGET test_assimp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ASSIMP_3.3.1_ROOT}/bin/Debug/assimp-vc143-mtd.dll"
        $<TARGET_FILE_DIR:test_assimp>)

target_link_libraries(test_main PRIVATE glfw3 ToolLib)
target_link_libraries(test_sun PRIVATE glfw3 ToolLib)
target_link_libraries(test_assimp PRIVATE glfw3 ToolLib assimp-vc143-mtd)
target_link_libraries(test_assimp_before PRIVATE glfw3 test_tools assimp-vc143-mtd ToolLib)