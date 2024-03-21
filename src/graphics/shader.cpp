#include "shader.h"

#include <iostream>
#include <fstream>

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
