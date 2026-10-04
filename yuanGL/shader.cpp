#include "pch.h"
#include "shader.h"

#include "shader_source.h"
#include "yuanGL.h"
#include "gl_call.h"
#include "matrix.h"

yuanGL::Shader::Shader(const char* filePath)
{
	ShaderSource src(filePath);

	GLCall(_id = glCreateProgram());

	unsigned int vertex_shader = compileShader(GL_VERTEX_SHADER, src.get_vertex_source());
	unsigned int fragment_shader = compileShader(GL_FRAGMENT_SHADER, src.get_fragment_source());

	GLCall(glAttachShader(_id, vertex_shader));
	GLCall(glAttachShader(_id, fragment_shader));
	GLCall(glLinkProgram(_id));
	GLCall(glValidateProgram(_id));

	GLCall(glDeleteShader(vertex_shader));
	GLCall(glDeleteShader(fragment_shader));
}

yuanGL::Shader::~Shader()
{
	unbind();
	GLCall(glDeleteProgram(_id));
}

void yuanGL::Shader::bind()
{
	GLCall(glUseProgram(_id));
}

void yuanGL::Shader::unbind()
{
	GLCall(glUseProgram(0));
}

void yuanGL::Shader::set_uniform_2f(const char* name, float v1, float v2)
{
	bind();
	GLCall(glUniform2f(get_uniform_location(name), v1, v2));
}

void yuanGL::Shader::set_uniform_3f(const char* name, float v1, float v2, float v3)
{
	bind();
	GLCall(glUniform3f(get_uniform_location(name), v1, v2, v3));
}

void yuanGL::Shader::set_uniform_i(const char* name, int v)
{
	bind();
	GLCall(glUniform1i(get_uniform_location(name), v));
}

void yuanGL::Shader::set_uniform_mat4(const char* name, const float* value)
{
	bind();
	GLCall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, value));
}

void yuanGL::Shader::set_uniform_mat4(const char* name, const Matrix& m)
{
	bind();
	GLCall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, m.data()));
}

int yuanGL::Shader::get_uniform_location(const char* name) const 
{
	const std::string name_str(name);
	auto findLocation = _uniform_locations.find(name_str);

	if (findLocation != _uniform_locations.end()) {
		return findLocation->second;
	}

	GLCall(int location = glGetUniformLocation(_id, name));
	if (location == -1) {
		std::cout << "uniform " << name << " not found" << std::endl;
		__debugbreak();
	}

	_uniform_locations[name_str] = location;

	return location;
}
