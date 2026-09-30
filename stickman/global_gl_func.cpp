#include "global_gl_func.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

unsigned int stickman::createShader(const std::string& vert, const std::string frag)
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

unsigned int stickman::createShader(ShaderProgramSources src)
{
    return createShader(src.vertexSource, src.fragmentSource);
}

unsigned int stickman::compileShader(unsigned int type, const std::string& src)
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

stickman::ShaderProgramSources stickman::parseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

void stickman::glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool stickman::glLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error]: " << error << std::endl;
        std::cout << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
