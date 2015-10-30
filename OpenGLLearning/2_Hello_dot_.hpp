#ifndef _2_HELLO_DOT__HPP_INCLUDED
#define _2_HELLO_DOT__HPP_INCLUDED

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace _2_Hello_dot_ {

    const char *title = "Hello dot!";

    static void errorCallback(int error, const char *description) {
        std::cerr << description << std::endl;
    }

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    static int main(int argc, const char *argv[]) {
        glfwSetErrorCallback(errorCallback);
        if (!glfwInit()) {
            std::cerr << glewGetErrorString(glGetError()) << std::endl;
            return EXIT_FAILURE;
        }
        GLFWwindow *window = glfwCreateWindow(1024, 768, title, nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            return EXIT_FAILURE;
        }
        glfwSetWindowPos(window, 100, 100);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetKeyCallback(window, keyCallback);
        if (glewInit() != GLEW_OK) {
            std::cerr << glewGetErrorString(glGetError()) << std::endl;
        }
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        using namespace glm;
        fvec3 vertex(0.0f, 0.0f, 0.0f);
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex, GL_STATIC_DRAW);
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glDrawArrays(GL_POINTS, 0, 1);
            glDisableVertexAttribArray(0);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_SUCCESS;
    }

}

#endif
