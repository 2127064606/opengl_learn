#include <glad/glad.h>
#include <Shader.hpp>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#define RESOURCES_PATH "../../resources/"
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
int main(){
    //初始化GLFW
    glfwInit();
    //设置主版本号为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //设置次版本号为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //设置OpenGL配置文件为核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //设置OpenGL前向兼容为真
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    //初始化glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置viewport
    glViewport(0, 0, 800, 600);
    //注册窗口大小改变的回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //查询opengl支持的最大顶点数
    int max_vertices;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertices);
    std::cout << "MAX_VERTEX_ATTRIBS: " << max_vertices << std::endl;
    
   //创建着色器
   Shader shader(RESOURCES_PATH "1.vert", RESOURCES_PATH "1.frag");


    //创建vao,vbo
    unsigned int vao,vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);

    //顶点数据
    float vertices[] = {
       // 位置              // 颜色           //纹理
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,    0.0f, 1.0f ,    // 左下
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    1.0f, 1.0f  ,   // 右下
   
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f ,    0.5f, 0.0f          // 顶部
};

    float vertices2[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
    };
    //索引数据
    unsigned int indices[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    
    //创建ebo 
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //将顶点数据copy到缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //设置顶点指针属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    //设置颜色指针属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    //设置纹理指针属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    //启用顶点属性
    glEnableVertexAttribArray(0);
    //启用颜色属性
    glEnableVertexAttribArray(1);
    //启用纹理属性
    glEnableVertexAttribArray(2);
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   //创建纹理
   unsigned int texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   //设置环绕方式
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   //设置过滤方式
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   //加载图片生成纹理
   int width, height, nr_channels;
   unsigned char* data = stbi_load(RESOURCES_PATH "pjpp2.jpg", &width, &height, &nr_channels, 0);
   if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
   }else{
    std::cout << "Failed to load texture" << std::endl;
   }
   stbi_image_free(data);

   //设置变换矩阵
   glm::mat4 trans;
//    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
   //trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
    float trans_array[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 1.0f
};
    while(!glfwWindowShouldClose(window)){
        //输入
        process_input(window);
        //渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // shader.setFloat("offsetx", -0.5f);
     
        //trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));    
        //使用着色器程序
        shader.use();
        unsigned int transform_loc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, trans_array);
        //绘制图形
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //交换前后缓冲
        glfwSwapBuffers(window);
        //事件处理
        glfwPollEvents();
    }
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
   
    //销毁窗口
    glfwDestroyWindow(window);
    //回收GLFW资源
    glfwTerminate();
    return 0;
}