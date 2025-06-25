#pragma once

#include <glad/glad.h>

#include <cstdio>

namespace Mnemos
{
    // TODO - Replace with Logger call
    inline void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        fprintf(stderr, "%s %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "[ERROR]" : "[DEBUG]"), message);
    }
}