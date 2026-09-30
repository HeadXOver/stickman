#pragma once

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) yuanGL::glClearError(); x; ASSERT(yuanGL::glLogCall(#x, __FILE__, __LINE__));

namespace yuanGL {

	bool glLogCall(const char* function, const char* file, int line);
	void glClearError();

}
