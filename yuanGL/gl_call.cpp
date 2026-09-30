#include "pch.h"
#include "gl_call.h"

bool yuanGL::glLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error]: " << error << std::endl;
        std::cout << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void yuanGL::glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}