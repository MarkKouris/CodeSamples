/*
 * file: Shader.h
 * author: Mark Kouris
 * brief: Shader Class
 *
 */

#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "glm/glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory> //shared pointer

class Shader
{
public:

  //constructor from files for vertex and frament shaders (non default)
  Shader(const char* vertexPath, const char* fragmentPath);

  void use(); //use the ID associated with shader

  //gettors for path strings for imgui
  std::string getVertPath(void) const;
  std::string getFragPath(void) const;
  unsigned int getModelLoc() const;
  unsigned int getID() const;

  // utility uniform functions, taken from learnOpenGL
  // ------------------------------------------------------------------------
  void setBool(const std::string& name, bool value) const
  {
      glUniform1i(glGetUniformLocation(data_->ID, name.c_str()), (int)value);
  }
  // ------------------------------------------------------------------------
  void setInt(const std::string& name, int value) const
  {
      glUniform1i(glGetUniformLocation(data_->ID, name.c_str()), value);
  }
  // ------------------------------------------------------------------------
  void setFloat(const std::string& name, float value) const
  {
      glUniform1f(glGetUniformLocation(data_->ID, name.c_str()), value);
  }


private:
  //check for shader link and compile errors
  void checkCompileErrors(unsigned int shader, std::string type);

  struct data 
  {
      unsigned int ID = 0; //the shaderID attached to this shader
      unsigned int modelLocation = 0; //used for accessing loc of model matrix
      std::string vertShaderPath_; // path to the vertex shader 
      std::string fragShaderPath_; // path to the fragment shader

      ~data();
  };

  std::shared_ptr<data> data_;

};
#endif