#include "graphics/shader.h"

#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    unsigned int shaderProgram = this->compile(vertexPath, fragmentPath);
    this->id = shaderProgram;
}

Shader::~Shader()
{
    glDeleteProgram(this->id);
}

void Shader::use()
{
    glUseProgram(this->id);
}

unsigned int Shader::load(const std::string &path, GLenum type)
{
    unsigned int shader = glCreateShader(type);
    std::ifstream in(path);
    if (!in.is_open())
    {
        std::cout << "Error opening file " << path << std::endl;
    }

    std::string code((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    const char *c_code = code.c_str();
    glShaderSource(shader, 1, &c_code, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        std::cout << path << std::endl;
    }

    return shader;
}

unsigned int Shader::compile(const std::string &vertexPath, const std::string &fragmentPath)
{
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vertexShader = this->load(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = this->load(fragmentPath, GL_FRAGMENT_SHADER);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void Shader::set(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}

void Shader::set(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::set(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::set(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(this->id, name.c_str()), x, y);
}

void Shader::set(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(this->id, name.c_str()), x, y, z);
}

void Shader::set(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(this->id, name.c_str()), x, y, z, w);
}

void Shader::set(const std::string &name, glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}