#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <Shader.hpp>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TEST_RESOURCE_PATH "../../test/test_resources/"
void window_size_callback(GLFWwindow* window, int width, int height){
   glViewport(0, 0, width, height);
}
void input_process(GLFWwindow* window){
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
   }
}
int main() {
   std::cout << std::filesystem::current_path().string() << std::endl;
   glfwInit();
   glfwInitHint(GLFW_VERSION_MAJOR, 3);
   glfwInitHint(GLFW_VERSION_MINOR, 3);
   glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwInitHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Window", NULL, NULL);
   if(!window){
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
   }
   glfwMakeContextCurrent(window);
  
   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
     std::cout << "Failed to initialize GLAD" << std::endl;
     glfwTerminate();
     return -1;
   }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
   glfwSetWindowSizeCallback(window, window_size_callback);

   unsigned int vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   unsigned int vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
   float vertices[] = {
       0.0f, 0.5f, 0.0f,1.0f,0.0f,0.0f,
       0.5f, -0.5f, 0.0f,0.0f,1.0f,0.0f,
       -0.5f, -0.5f, 0.0f,0.0f,0.0f,1.0f
   };
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  Shader shader(TEST_RESOURCE_PATH "t1.vert", TEST_RESOURCE_PATH "t1.frag");

  
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   while(!glfwWindowShouldClose(window)){
     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT);
     input_process(window);
     shader.use();
     glDrawArrays(GL_TRIANGLES, 0, 3);
     glfwSwapBuffers(window);
     glfwPollEvents();
   }
   return 0;
}