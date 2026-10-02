#pragma once

#include <unordered_map>
#include <string>

namespace yuanGL {

	class Matrix;

	class Shader {

	public:
		Shader(const char* filePath);
		~Shader();

		void bind();
		void unbind();

		void set_uniform_3f(const char* name, float v1, float v2, float v3);
		void set_uniform_i(const char* name, int v);
		void set_uniform_mat4(const char* name, const float* value);
		void set_uniform_mat4(const char* name, const Matrix& m);

		int get_uniform_location(const char* name) const;

	private:
		unsigned int _id;

		mutable std::unordered_map<std::string, int> _uniform_locations;
	};

}
