#include "pch.h"

#include "yuanGL.h"

#include "gl_call.h"

void yuanGL::glfw_use_3_3_core()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void yuanGL::glfw_print_version()
{
    std::cout << glGetString(GL_VERSION) << std::endl;
}

void yuanGL::glfw_init() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        __debugbreak();
        exit(EXIT_FAILURE);
    }
}

void yuanGL::blend_alpha()
{
    GLCall(glEnable(GL_BLEND));

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void yuanGL::set_swap_interval(bool v)
{
    glfwSwapInterval(v ? 1 : 0);
}

unsigned int yuanGL::createShader(const std::string& vert, const std::string frag)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vert);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, frag);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int yuanGL::compileShader(unsigned int type, const std::string& src)
{
    unsigned int id = glCreateShader(type);
    const char* source = src.c_str();
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
