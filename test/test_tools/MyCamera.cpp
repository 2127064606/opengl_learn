#include <MyCamera.hpp>


void MyCamera::updateCameraVectors(){
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}

void MyCamera::processKeyboardInput(GLFWwindow* window, float delta_time){
    float velocity = DEFAULT_MOVEMENT_SPEED * delta_time;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        position += front * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        position -= front * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        position -= right * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        position += right * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        position -= up * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        position += up * velocity;
    }
}

void MyCamera::processMouseInput(GLFWwindow* window, float xoffset, float yoffset){
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch +=yoffset;
    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if(pitch < -89.0f){
        pitch = -89.0f;
    }
    updateCameraVectors();
}

void MyCamera::processScrollInput(GLFWwindow* window, float yoffset){
    zoom -= yoffset;
    if(zoom < 1.0f){
        zoom = 1.0f;
    }
    if(zoom > 45.0f){
        zoom = 45.0f;
    }
}

glm::mat4 MyCamera::getViewMatrix(){
    return glm::lookAt(position, position + front, world_up);
}