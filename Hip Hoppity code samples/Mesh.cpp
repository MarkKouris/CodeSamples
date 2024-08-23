/*
 * file: Mesh.cpp
 * author: Mark Kouris (mark.kouris\@digipen.edu)
 * brief: the interface of the Mesh class,
 *        this will be a super class for specific meshes.
 *        Both Ctors makes a square mesh for now.
 *
 * This class follows the implementation from Mesh.h
 * 
 */

#include "Log.h"
#include "Mesh.h" //has glm included
#include "glm/glm/gtc/type_ptr.inl"
#include "glm/glm/gtc/matrix_transform.hpp"

#define VERTICIES_COUNT 32
#define INDICIES_COUNT 6

//default Mesh ctor, makes square mesh
Mesh::Mesh()
{
    data_ = std::make_shared<data>();
    data_->center_ = glm::vec4(0, 0, 1.f, 1.f);     //centered at origin by default
    data_->scale_ = glm::vec4(0.5f, 1.f, 1.f, 1.f); // this is the length of the X and Y axis, half is offset

    float vertices[] = {
        //positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] =
    {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    //generates vertex array and buffers.
    glGenVertexArrays(1, &data_->VAO);
    glGenBuffers(1, &data_->VBO);
    glGenBuffers(1, &data_->EBO);

    //bind the objects to the arrays of objects
    glBindVertexArray(data_->VAO);

    //link data
    glBindBuffer(GL_ARRAY_BUFFER, data_->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //link data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //set position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //set color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //set texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
   
}

//nondefault ctor, makes square mesh centered around vector
Mesh::Mesh(glm::vec4 center, glm::vec4 scale)
{
    data_ = std::make_shared<data>();
    data_->center_ = center; // the world coordinate to base mesh on
    data_->scale_ = scale;   // this is the length of the X and Y axis, half is offset

    //max and min points calculated for readability
    float minX = data_->center_.x - data_->scale_.x / 2;
    float maxX = data_->center_.x + data_->scale_.x / 2;
    float minY = data_->center_.y - data_->scale_.y / 2;
    float maxY = data_->center_.y + data_->scale_.y / 2;


    //calc edges using + or - the dimensions for x and y
    float vertices[] =
    {
        //position          //color values      //texture coords
        maxX, maxY, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,      //upper right corner,  point 0
        maxX, minY, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,      //bottom right corner, point 1
        minX, minY, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,      //bottem left corner,  point 2
        minX, maxY, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,      //upper left corner,   point 3

    };

    unsigned int indices[] =
    {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3  // second Triangle
    };

    //generates the buffers and vertex array for use
    glGenVertexArrays(1, &data_->VAO);
    glGenBuffers(1, &data_->VBO);
    glGenBuffers(1, &data_->EBO);

    //bind the objects to the arrays of objects
    glBindVertexArray(data_->VAO);

    //link data
    glBindBuffer(GL_ARRAY_BUFFER, data_->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //link data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //set position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //set color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //set texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

//default dtor, cleans up all buffers and arrays.
Mesh::data::~data()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

//GETTORS

//this is the center point of the mesh (in NDC)
glm::vec4 Mesh::center(void) const
{
    return data_->center_;
}

//this is the length of the width and height based on NDC
glm::vec4 Mesh::scale(void) const
{
    return data_->scale_;
}

//Will not be constant when we make more than just square meshes
int Mesh::verticiesCount(void) const
{
    return VERTICIES_COUNT;
}

//Will not be constant when we make more than just square meshes
int Mesh::indiciesCount(void) const
{
    return INDICIES_COUNT;
}

unsigned int Mesh::getVAO()const
{
    return data_->VAO;
}
unsigned int Mesh::getVBO()const
{
    return data_->VBO;
}

unsigned int Mesh::getEBO()const
{
    return data_->EBO;
}