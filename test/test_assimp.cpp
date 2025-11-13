#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Camera.hpp>
#include <Shader.hpp>
#include <Model.hpp>
#include <glm/glm.hpp>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TEST_RESOURCE_PATH "../../test/test_resources/"
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
float lastTime = 0.0f;
bool firstMouse = true;

void buffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mousemovement_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float yoffset = lastY - ypos;
    float xoffset = xpos - lastX;
    lastX = xpos;
    lastY = ypos;
    camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.processScrollMovement(static_cast<float>(yoffset));
}

void process_input(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    camera.processKeyboardInput(window, deltaTime);
}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Assimp", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetWindowSizeCallback(window, buffer_size_callback);
    glfwSetCursorPosCallback(window, mousemovement_callback);
    glfwSetScrollCallback(window, scroll_callback);

    Shader shader(TEST_RESOURCE_PATH "assimp.vert", TEST_RESOURCE_PATH "assimp.frag");
    Model mod(TEST_RESOURCE_PATH "backpack/backpack.obj");

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        process_input(window, deltaTime);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        shader.setMat4("model", model);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        mod.Draw(shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}