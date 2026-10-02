#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace yuanGL {

	class Transformer;

	enum MatrixType : uint32_t {
		Quelque = 1u,
		Identity = 1u << 1,
		Translate = 1u << 2,
		Rotate = 1u << 3,
		Scale = 1u << 4,
		Homo = 1u << 5,
		Ortho = 1u << 6,
	};

	class Matrix : public glm::mat4 {

	public:
		Matrix();
		Matrix(float s);
		Matrix(const glm::mat4& m);
		Matrix(const Transformer& t);
		Matrix(MatrixType type, float f1, float f2, float f3, float f4);
		Matrix(MatrixType type, float f1, float f2, float f3, float f4, float f5, float f6);
		Matrix(MatrixType type, float f1, float f2);
		Matrix(MatrixType type, float f1);

		void set_to_orth(float left, float right, float bottom, float top);
		void add_translate(float x, float y);
		void set_translate(float x, float y);

		const float* data() const noexcept;
	};

}
