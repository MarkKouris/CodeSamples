/*
 * file: Shader.cpp
 * author: Mark Kouris
 * brief: This class is for handling the creation of shaders.
 * Will always use input from 
 */

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"


//constructor, this constructs a shader from file, non default
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    data_ = std::make_shared<data>();
    //retrieve the vertex/fragment source code from filePath
    //strings to hold shader code
    std::string vertexCode;
    std::string fragmentCode;
   
    //input files for code
    std::ifstream vertShaderFile;
    std::ifstream fragShaderFile;

    // make sure ifstream objects can throw exceptions with failbit/ badbit
    vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files using given path names
        vertShaderFile.open(vertexPath);
        fragShaderFile.open(fragmentPath);
        std::stringstream vertShaderStream, fragShaderStream;
        // read file's buffer contents into streams
        vertShaderStream << vertShaderFile.rdbuf();
        fragShaderStream << fragShaderFile.rdbuf();
        // close file handlers
        vertShaderFile.close();
        fragShaderFile.close();
        // convert stream into string
        vertexCode = vertShaderStream.str();
        fragmentCode = fragShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        e;
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    //create const strings for shader code
    const char* vertShaderCode = vertexCode.c_str();
    const char* fragShaderCode = fragmentCode.c_str();

    // compile shaders
    unsigned int vertex;
    unsigned int fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertShaderCode, NULL);
    glCompileShader(vertex);

    //use helper to check for compile/link errors
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragShaderCode, NULL);
    glCompileShader(fragment);
    //use helper to check for compile/link errors
    checkCompileErrors(fragment, "FRAGMENT");

    // shader Program
    data_->ID = glCreateProgram();
    glAttachShader(data_->ID, vertex);
    glAttachShader(data_->ID, fragment);
    glLinkProgram(data_->ID);
    //use helper to check for compile/link errors
    checkCompileErrors(data_->ID, "PROGRAM");

    data_->vertShaderPath_ = vertexPath;
    data_->fragShaderPath_ = fragmentPath;
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    data_->modelLocation = glGetUniformLocation(data_->ID, "model");

}

//default dtor, frees shader
Shader::data::~data()
{
    //free memory
    glDeleteProgram(ID);
}

//use the current shader
void Shader::use()
{
    glUseProgram(data_->ID);
}

//gettor for the vertex shader path
std::string Shader::getVertPath(void) const
{
    return data_->vertShaderPath_;
}

//gettor for fragment shader path.
std::string Shader::getFragPath(void) const
{
    return data_->fragShaderPath_;
}

unsigned int Shader::getModelLoc() const
{
    return data_->modelLocation;
}

unsigned int Shader::getID() const
{
    return data_->ID;
}

//check for shader link and compile errors
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{//taken directly from learn openGL
    int success;
    char infoLog[1024]; //error text buffer

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

