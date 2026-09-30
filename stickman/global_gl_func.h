#pragma once

#include <string>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) stickman::glClearError(); x; ASSERT(stickman::glLogCall(#x, __FILE__, __LINE__));

namespace stickman{

	struct ShaderProgramSources {
		std::string vertexSource;
		std::string fragmentSource;
	};

	unsigned int createShader(const std::string& vert, const std::string frag);
	unsigned int createShader(ShaderProgramSources src);

	unsigned int compileShader(unsigned int type, const std::string& src);

	ShaderProgramSources parseShader(const std::string& filePath);

	void glClearError();

	bool glLogCall(const char* function, const char* file, int line);
	
}
