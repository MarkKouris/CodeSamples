/*
 * file: Mesh.h
 * author: Mark Kouris (mark.kouris\@digipen.edu)
 * brief: the interface of the Mesh class,
 *        this will a super class for specific meshes.
 *
 * Meshes are the "canvases" that display our sprites
 *
 */
#pragma once
#include "glm/glm/glm.hpp"
#include <glad/glad.h>
#include "Transform.h" /* Used for Sprite and connecting components */
#include <array>
#include <memory>   //std::shared_ptr
#include "glm/glm/mat4x4.hpp"

class Mesh
{
public:
    Mesh();  //default ctor, creates mesh around 0,0 and scale is 1,1
    Mesh(glm::vec4 center, glm::vec4 scale); //greats a mesh based around a center point.

    //gettors
    glm::vec4 center(void) const;
    glm::vec4 scale(void) const;
    unsigned int getVAO()const;
    unsigned int getVBO()const;
    unsigned int getEBO()const;
    int verticiesCount(void) const;
    int indiciesCount(void) const;

private:
    struct data
    {
        unsigned int VAO; //used to bind the vertex array
        unsigned int VBO; //the vertex buffer object
        unsigned int EBO; //the element buffer object
        glm::vec4 center_; //center for this mesh
        glm::vec4 scale_;  //the scale for this mesh

        ~data();
    };

    //shared pointer to have multiple sprites reference this mesh
    std::shared_ptr<data> data_; 
   

};