#include "window/window.h"

#include <iostream>

Window::Window(int width, int height, const std::string &title)
{
    window = this->create(width, height, title);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow *Window::create(int width, int height, const std::string &title)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }

    return window;
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

bool Window::isOpen()
{
    glfwPollEvents();
    return !glfwWindowShouldClose(window);
}

void Window::close()
{
    glfwSetWindowShouldClose(this->window, true);
}

bool Window::isKeyPressed(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}