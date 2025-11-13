#pragma once
#ifndef INFO_HPP
#define INFO_HPP
#include <iostream>
#include <ctime>

class Info{
    public:
        static void info(const std::string& msg){
            std::time_t time = std::time(nullptr);
            std::cout << "INFO: " << "[" << std::ctime(&time) << "] " << msg << std::endl;
        }
        static void error(const std::string& msg){
            std::time_t time = std::time(nullptr);
            std::cout << "ERROR: " << "[" << std::ctime(&time) << "] " << msg << std::endl;
        }
        
};  

#define INFO(...) Info::info(__VA_ARGS__)
#define ERROR(...) Info::error(__VA_ARGS__)


#endif
