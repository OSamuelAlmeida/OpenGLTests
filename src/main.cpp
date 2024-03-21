#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/window.h"
#include "graphics/shader.h"

void processInput(Window &window);

int main()
{
    Window window(800, 600, "OpenGL Tests");

    Shader shader("shaders/vertex.vert.glsl", "shaders/fragment.frag.glsl");

    float vertices[] = {
        -0.2f, -0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
        0.0f, 0.2f, 0.0f};

    float vertices2[] = {
        -0.3f, -0.8f, 0.0f,
        0.3f, -0.8f, 0.0f,
        0.0f, -0.6f, 0.0f};

    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    while (window.isOpen())
    {
        processInput(window);

        glClearColor(0.0f, 0.392f, 0.686f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window.swapBuffers();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);

    return 0;
}

void processInput(Window &window)
{
    if (window.isKeyPressed(GLFW_KEY_ESCAPE) || (window.isKeyPressed(GLFW_KEY_W) && window.isKeyPressed(GLFW_KEY_LEFT_SUPER)))
    {
        window.close();
    }
}