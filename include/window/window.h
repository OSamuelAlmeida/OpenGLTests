#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    void swapBuffers();
    bool isOpen();
    void close();

    bool isKeyPressed(int key);

private:
    GLFWwindow *window;

    GLFWwindow *create(int width, int height, const std::string &title);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};