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
    void set(const std::string &name, bool value) const;
    void set(const std::string &name, int value) const;
    void set(const std::string &name, float value) const;
    void set(const std::string &name, float x, float y) const;
    void set(const std::string &name, float x, float y, float z) const;
    void set(const std::string &name, float x, float y, float z, float w) const;

private:
    unsigned int id;

    unsigned int load(const std::string &path, GLenum type);
    unsigned int compile(const std::string &vertexPath, const std::string &fragmentPath);
    void checkCompileErrors(unsigned int shader, std::string type);
};