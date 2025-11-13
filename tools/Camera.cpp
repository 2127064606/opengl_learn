#include <Camera.hpp>


void Camera::processKeyboardInput(GLFWwindow *window, float deltatime){
    float velocity = moveSpeed * deltatime;
    if(glfwGetKey(window, GLFW_KEY_W)){
        position += front * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_S)){
        position -= front * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_A)){
        position -= right * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_D)){
        position += right * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_Q)){
        position -= up * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_E)){
        position += up * velocity;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch){
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    if(constrainPitch){
        if(pitch > 89.0f){
            pitch = 89.0f;
        }
        if(pitch < -89.0f){
            pitch = -89.0f;
        }
    }
    
    updateCameraVectors();
}

void Camera::processScrollMovement(float yoffset){
    zoom -= yoffset;
    if(zoom < 1.0f){
        zoom = 1.0f;
    }
    if(zoom > 45.0f){
        zoom = 45.0f;
    }
}

void Camera::updateCameraVectors(){
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}