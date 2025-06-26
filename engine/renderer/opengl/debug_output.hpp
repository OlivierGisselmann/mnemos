#pragma once

#include <core/logging/logger_manager.hpp>

#include <glad/glad.h>

namespace Mnemos
{
    // TODO - Replace with Logger call
    inline void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        LOGF((type == GL_DEBUG_TYPE_ERROR) ? LogLevel::ERR : LogLevel::DEBUG) << message;
    }
}