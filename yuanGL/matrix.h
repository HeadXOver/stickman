#pragma once

namespace yuanGL {

	enum class MatrixType : uint32_t {
		None = 1u,
		Identity = 1u << 1,
		Translate = 1u << 2,
		Rotate = 1u << 3,
		Scale = 1u << 4,
		Homo = 1u << 5,
		Ortho = 1u << 6,
	};

	class Matrix {

	public:
		Matrix();
		Matrix(float s);
		Matrix(const glm::mat4& m);
		Matrix(MatrixType type, float f1, float f2, float f3, float f4);
		Matrix(MatrixType type, float f1, float f2, float f3, float f4, float f5, float f6);
		~Matrix();

		void set_to_orth(float left, float right, float bottom, float top);

		const float* data() const noexcept;

	private:

		MatrixType _type = MatrixType::None;
		glm::mat4* _m;
	};

}
