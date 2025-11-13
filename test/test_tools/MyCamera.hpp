#pragma once
#ifndef MY_CAMERA_HPP
#define MY_CAMERA_HPP
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


const float DEFAULT_YAW = -90.0f;
const float DEFAULT_PITCH = 0.0f;
const float DEFAULT_SENSITIVITY = 0.1f;
const glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 DEFAULT_WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const float DEFAULT_ZOOM = 45.0f;
const float DEFAULT_MOVEMENT_SPEED = 2.5f;



class MyCamera
{
    public:
     glm::vec3 position; //相机位置
     glm::vec3 front; //前方
     glm::vec3 up; //上方
     glm::vec3 right; //右方
     glm::vec3 world_up; //世界上方
     float yaw; //偏航角
     float pitch; //俯仰角
     float sensitivity; //灵敏度
     float zoom;
     float movement_speed;
    //构造函数

    /// @brief 相机类构造函数
    /// @param position 相机位置
    /// @param world_up 世界上方
    /// @param yaw 偏航角
    /// @param pitch 俯仰角
    /// @param sensitivity 灵敏度
    MyCamera(glm::vec3 position = DEFAULT_POSITION, glm::vec3 world_up = DEFAULT_WORLD_UP, float yaw = DEFAULT_YAW, float pitch = DEFAULT_PITCH, float sensitivity = DEFAULT_SENSITIVITY, float zoom = DEFAULT_ZOOM, float movement_speed = DEFAULT_MOVEMENT_SPEED){
        this->position = position;
        this->world_up = world_up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->sensitivity = sensitivity;
        this->zoom = zoom;
        this->movement_speed = movement_speed;
        updateCameraVectors();
    }
    /// @brief 获取视图矩阵
    /// @return glm::mat4 视图矩阵
    glm::mat4 getViewMatrix();
    void processMouseInput(GLFWwindow* window, float xoffset, float yoffset);
    void processKeyboardInput(GLFWwindow* window, float delta_time);
    void processScrollInput(GLFWwindow* window, float yoffset);
    private:
        void updateCameraVectors();
        
};

#endif