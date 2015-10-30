#ifndef _6_TRANSLATION_TRANSFORMATION_HPP_INCLUDED
#define _6_TRANSLATION_TRANSFORMATION_HPP_INCLUDED

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "helpers.hpp"

namespace _6_Translation_Transformation {

    const char *title = "Translation Transformation";

    const char *vertexShaderSource = R"VS(

#version 400

layout (location = 0) in vec3 Position;

uniform mat4 World;

void main() {
    gl_Position = World * vec4(Position, 1.0);
}

)VS";

    const char *fragmentShaderSource = R"FS(

#version 400

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}

)FS";

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
        GLuint vertexShader;
        std::string log;
        if (!helpers::compileShader(GL_VERTEX_SHADER, vertexShaderSource, vertexShader, log)) {
            std::cerr << "Error compiling vertexShader: " << log << std::endl;
            return EXIT_FAILURE;
        }
        GLuint fragmentShader;
        if (!helpers::compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource, fragmentShader, log)) {
            std::cerr << "Error compiling fragmentShader: " << log << std::endl;
            return EXIT_FAILURE;
        }
        GLuint program;
        if (!helpers::linkProgram({vertexShader, fragmentShader}, program, log)) {
            std::cerr << "Error linking program: " << log << std::endl;
            return EXIT_FAILURE;
        }
        glValidateProgram(program);
        glUseProgram(program);
        auto worldLocation = glGetUniformLocation(program, "World");
        GLfloat scale = 0.0f;
        using namespace glm;
        vec3 vertices[3] = {
            {-1.0f, -1.0f, 0.0f},
            {1.0f, -1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f}
        };
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            scale += 0.001f;
            mat4 world(1.0f);
            world[0][3] = sinf(scale);
            glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &world[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
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
