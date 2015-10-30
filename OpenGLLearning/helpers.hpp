#ifndef HELPERS_HPP_INCLUDED
#define HELPERS_HPP_INCLUDED

#include <string>
#include <vector>
#include <GL/glew.h>

namespace helpers {

    bool compileShader(GLenum type, const char *source, GLuint &handler, std::string &log) {
        handler = glCreateShader(type);
        auto length = (GLint)strlen(source);
        glShaderSource(handler, 1, &source, &length);
        glCompileShader(handler);
        GLint success;
        glGetShaderiv(handler, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar buffer[1024];
            glGetShaderInfoLog(handler, sizeof(buffer), nullptr, buffer);
            log = buffer;
            glDeleteShader(handler);
            handler = NULL;
        } else {
            log = "Complie succeeded.";
        }
        return success == GL_TRUE;
    }

    bool linkProgram(std::vector<GLuint> shaders, GLuint &handler, std::string &log) {
        handler = glCreateProgram();
        for (auto &&shader : shaders) {
            glAttachShader(handler, shader);
        }
        glLinkProgram(handler);
        GLint success;
        glGetProgramiv(handler, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar buffer[1024];
            glGetProgramInfoLog(handler, sizeof(buffer), nullptr, buffer);
            log = buffer;
            glDeleteProgram(handler);
            handler = NULL;
        } else {
            log = "Link succeeded.";
        }
        return success == GL_TRUE;
    }

}

#endif
