#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    void use();

private:
    unsigned int id;

    unsigned int load(const std::string &path, GLenum type);
    unsigned int compile(const std::string &vertexPath, const std::string &fragmentPath);
    void checkCompileErrors(unsigned int shader, std::string type);
};