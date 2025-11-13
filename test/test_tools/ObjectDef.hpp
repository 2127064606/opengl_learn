#pragma once
#ifndef OBJECT_DEF_HPP
#define OBJECT_DEF_HPP

enum triangle_vertex_index{
    TRIANGLE1
};

enum square_vertex_index{
    SQUARE1
};

enum square_3d_vertex_index{
    SQUARE3D1
};
const float triangle1[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
} ;

const  float vertices[] = {
       -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
       0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
       -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

const unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

const float square_3d[] = {
     // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

class ObjectDef{
public:
    static const float TRIANGLE_VERTICES[];
    static const float* getTriangleVertices(triangle_vertex_index index){
        switch(index){
            case TRIANGLE1:
                return triangle1;
        }
    }
     static size_t getTriangleVerticesSize(triangle_vertex_index index){
        switch(index){
            case TRIANGLE1:
                return sizeof(triangle1);  // 正确返回数组的实际大小
            default:
                return 0;
        }
    }

    static const float* getSquareVertices(square_vertex_index index){
        switch(index){
            case SQUARE1:
                return vertices;
        }
    }
    static size_t getSquareVerticesSize(square_vertex_index index){
        switch(index){
            case SQUARE1:
                return sizeof(vertices);  // 正确返回数组的实际大小
            default:
                return 0;
        }
    }
    static const unsigned int* getSquareIndices(square_vertex_index index){
        switch(index){
            case SQUARE1:
                return indices;
        }
    }
    static size_t getSquareIndicesSize(square_vertex_index index){
        switch(index){
            case SQUARE1:
                return sizeof(indices);  // 正确返回数组的实际大小
            default:
                return 0;
        }
    }
    static const float* getSquare3DVertices(square_3d_vertex_index index){
        switch(index){
            case SQUARE3D1:
                return square_3d;
        }
    }
    static size_t getSquare3DVerticesSize(square_3d_vertex_index index){
        switch(index){
            case SQUARE3D1:
                return sizeof(square_3d);  // 正确返回数组的实际大小
            default:
                return 0;
        }
    }


};

#endif