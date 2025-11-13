#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <MyCamera.hpp>
#include <MyShader.hpp>
#include <Shader.hpp>
#include <ObjectDef.hpp>
#include <MyMesh.hpp>
#include <MyModel.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TEST_RESOURCE_PATH "../../test/test_resources/"

MyCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;
float lastTime = 0.0f;
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera.processMouseInput(window, xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.processScrollInput(window, yoffset);
}
int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test", NULL, NULL);
    if(!window){
        std::cout << "创建窗口失败" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "初始化GLAD失败" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetWindowSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // unsigned int vbo, vao;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, ObjectDef::getSquare3DVerticesSize(SQUARE3D1), ObjectDef::getSquare3DVertices(SQUARE3D1), GL_STATIC_DRAW);
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // // unsigned int ebo;
    // // glGenBuffers(1, &ebo);
    // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // // glBufferData(GL_ELEMENT_ARRAY_BUFFER, ObjectDef::getSquareIndicesSize(SQUARE1), ObjectDef::getSquareIndices(SQUARE1), GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);
    // glEnableVertexAttribArray(2);
    // glBindVertexArray(0);
    MyShader shader(TEST_RESOURCE_PATH "assimp.vert", TEST_RESOURCE_PATH "assimp.frag");
    MyModel mod(TEST_RESOURCE_PATH "backpack/backpack.obj");
    // Texture t1;
    // t1.id = t1.loadTexture(TEST_RESOURCE_PATH "w2.jpg");
    // Texture t2;
    // t2.id = t2.loadTexture(TEST_RESOURCE_PATH "b2.jpg");
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        camera.processKeyboardInput(window, deltaTime);
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        //shader.setVec3("viewPos", camera.position);
        // shader.setVec3("pointLight.position", glm::vec3(1.2f, 1.0f, 2.0f));
        // shader.setVec3("pointLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        // shader.setVec3("pointLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        // shader.setVec3("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        // shader.setFloat("material.shininess", 32.0f);
        // shader.setFloat("pointLight.constant", 1.0f);
        // shader.setFloat("pointLight.linear", 0.09f);
        // shader.setFloat("pointLight.quadratic", 0.032f);
        // shader.setVec3("parralLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        // shader.setVec3("parralLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        // shader.setVec3("parralLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        // shader.setVec3("parralLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        // shader.setVec3("spotLight.position", camera.position);
        // shader.setVec3("spotLight.direction", camera.front);
        // shader.setVec3("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        // shader.setVec3("spotLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        // shader.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        // shader.setFloat("spotLight.constant", 1.0f);
        // shader.setFloat("spotLight.linear", 0.09f);
        // shader.setFloat("spotLight.quadratic", 0.032f);
        // shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        // shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        mod.draw(shader);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, t1.id);
        // shader.setInt("material.diffuse", 0);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, t2.id);
        // shader.setInt("material.specular", 1);
        // glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, ObjectDef::getSquareIndicesSize(SQUARE1), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
}