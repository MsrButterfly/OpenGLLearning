#ifndef _1_OPEN_A_WINDOW_HPP_INCLUDED
#define _1_OPEN_A_WINDOW_HPP_INCLUDED

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace _1_Open_a_window {

    const char *title = "Open a window";

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
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_SUCCESS;
    }

}

#endif
