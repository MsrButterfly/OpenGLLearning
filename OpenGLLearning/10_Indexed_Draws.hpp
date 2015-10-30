#ifndef _10_INDEXED_DRAWS_HPP_INCLUDED
#define _10_INDEXED_DRAWS_HPP_INCLUDED

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "helpers.hpp"

namespace _10_Indexed_Draws {

    const char *title = "Indexed Draws";

    const char *vertexShaderSource = R"VS(

#version 400

uniform mat4 World;

layout (location = 0) in vec3 Position;

out vec4 Color;

void main() {
    gl_Position = World * vec4(Position, 1.0);
    Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
}

)VS";

    const char *fragmentShaderSource = R"FS(

#version 400

in vec4 Color;
out vec4 FragColor;

void main() {
    FragColor = Color;
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
        using namespace glm;
        vec3 vertices[4] = {
            {-1.0f, -1.0f, 0.0f},
            {0.0f, -1.0f, 1.0f},
            {1.0f, -1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f}
        };
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        GLuint indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
        };
        GLuint ibo = 0;
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        GLfloat scale = 0.0f;
        auto worldLocation = glGetUniformLocation(program, "World");
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            scale += 0.01f;
            mat4 world = {
                cosf(scale), 0.0f, -sinf(scale), 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                sinf(scale), 0.0f, cosf(scale), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
            glUniformMatrix4fv(worldLocation, 1, GL_FALSE, &world[0][0]);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
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
