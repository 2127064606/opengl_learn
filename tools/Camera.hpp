#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;



class Camera{
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        float pitch;
        float yaw;
        float zoom;
        float sensitivity;   
        float moveSpeed;   
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        {
            this->position = position;
            this->worldUp = up;
            this->yaw = yaw;
            this->pitch = pitch;
            this->zoom = ZOOM;
            this->sensitivity = SENSITIVITY;
            this->moveSpeed = SPEED;
            updateCameraVectors();
        }
        glm::mat4 getViewMatrix(){
            return glm::lookAt(position, position + front, up);
        }
        void processKeyboardInput(GLFWwindow *window, float deltaTime);
        void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void processScrollMovement(float yoffset);
    private:
        void updateCameraVectors();

};





#endif