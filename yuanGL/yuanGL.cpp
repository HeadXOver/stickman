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

int yuanGL::char_to_glfw_key(char c)
{
    switch (c) {
    case ' ':
        return GLFW_KEY_SPACE;
    case ',':
        return GLFW_KEY_COMMA;
    case '.':
        return GLFW_KEY_PERIOD;
        case '/':
        return GLFW_KEY_SLASH;
    case ';':
        return GLFW_KEY_SEMICOLON;
    case '\'':
        return GLFW_KEY_APOSTROPHE;
    case '[':
        return GLFW_KEY_LEFT_BRACKET;
    case ']':
        return GLFW_KEY_RIGHT_BRACKET;
    case '\\':
        return GLFW_KEY_BACKSLASH;
    case '-':
        return GLFW_KEY_MINUS;
    case '=':
        return GLFW_KEY_EQUAL;
    case '`':
        return GLFW_KEY_GRAVE_ACCENT;
    default:
        char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));

        if (upper < 'A' || upper > 'Z')
            return GLFW_KEY_UNKNOWN;

        return GLFW_KEY_A + (upper - 'A');
    }

    return GLFW_KEY_UNKNOWN;
}

constexpr int yuanGL::char_to_glfw_key_constexpr(char c)
{
    switch (c) {
    case ' ':
        return GLFW_KEY_SPACE;
    case ',':
        return GLFW_KEY_COMMA;
    case '.':
        return GLFW_KEY_PERIOD;
    case '/':
        return GLFW_KEY_SLASH;
    case ';':
        return GLFW_KEY_SEMICOLON;
    case '\'':
        return GLFW_KEY_APOSTROPHE;
    case '[':
        return GLFW_KEY_LEFT_BRACKET;
    case ']':
        return GLFW_KEY_RIGHT_BRACKET;
    case '\\':
        return GLFW_KEY_BACKSLASH;
    case '-':
        return GLFW_KEY_MINUS;
    case '=':
        return GLFW_KEY_EQUAL;
    case '`':
        return GLFW_KEY_GRAVE_ACCENT;
    default:
        if(c >= 'A' && c <= 'Z') return GLFW_KEY_A + (c - 'A');

        if (c >= 'a' && c <= 'z') return GLFW_KEY_A + (c - 'a');
    }

    return GLFW_KEY_UNKNOWN;
}
