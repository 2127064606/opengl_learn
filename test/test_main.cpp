#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <Shader.hpp>
#include <stb_image.h>
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
       -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
       0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
       -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
   };
   unsigned int indexs[] ={
       0, 1, 2,
       0, 2, 3,
   };

   unsigned int ebo;
   glGenBuffers(1, &ebo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  Shader shader(TEST_RESOURCE_PATH "t1.vert", TEST_RESOURCE_PATH "t1.frag");

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width, height, channels;
  unsigned char *data = stbi_load(TEST_RESOURCE_PATH "w2.jpg", &width, &height, &channels, 0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }else{
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   while(!glfwWindowShouldClose(window)){
     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT);
     input_process(window);
     shader.use();
     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
     glfwSwapBuffers(window);
     glfwPollEvents();
   }
   return 0;
}