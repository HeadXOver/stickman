#include "pch.h"
#include "matrix.h"

#include "transformer.h"

yuanGL::Matrix::Matrix() : glm::mat4(1.f) {}
yuanGL::Matrix::Matrix(float s) : glm::mat4(s) {}
yuanGL::Matrix::Matrix(const glm::mat4& m) : glm::mat4(m) {}

yuanGL::Matrix::Matrix(const Transformer& t) :
    glm::mat4(1.f)
{
	operator[](0)[0] = t.w();
	operator[](1)[1] = t.h();
	*this = glm::rotate(glm::mat4(1.0f), t.r(), glm::vec3(0.0f, 0.0f, 1.0f)) * (*this);
	operator[](3)[0] = t.x();
	operator[](3)[1] = t.y();
}

yuanGL::Matrix::Matrix(MatrixType type, float f1, float f2, float f3, float f4)
{
	switch (type) {
	case MatrixType::Ortho:
		*this = glm::ortho(f1, f2, f3, f4, -1.f, 1.f);
		break;
	default:
		std::cout << "Error: MatrixType not supported" << std::endl;
		__debugbreak();
	}
}

yuanGL::Matrix::Matrix(MatrixType type, float f1, float f2, float f3, float f4, float f5, float f6)
{
	switch (type) {
	case MatrixType::Ortho:
		*this = glm::ortho(f1, f2, f3, f4, f5, f6);
		break;
	default:
		std::cout << "Error: MatrixType not supported" << std::endl;
		__debugbreak();
	}
}

yuanGL::Matrix::Matrix(MatrixType type, float f1, float f2) :
    glm::mat4(1.f)
{
	switch (type) {
	case MatrixType::Scale:
		(*this)[0][0] = f1;
		(*this)[1][1] = f2;
		break;
	default:
		std::cout << "Error: MatrixType not supported" << std::endl;
		__debugbreak();
	}
}

yuanGL::Matrix::Matrix(MatrixType type, float f1) :
	glm::mat4(1.f)
{
	switch (type) {
	case MatrixType::Scale:
		operator[](0)[0] = f1;
		operator[](1)[1] = f1;
		break;
	default:
		std::cout << "Error: MatrixType not supported" << std::endl;
		__debugbreak();
	}
}

void yuanGL::Matrix::set_to_orth(float left, float right, float bottom, float top)
{
	*this = glm::ortho(left, right, bottom, top, -1.f, 1.f);
}

void yuanGL::Matrix::add_translate(float x, float y)
{
	operator[](3)[0] += x;
	operator[](3)[1] += y;
}

void yuanGL::Matrix::set_translate(float x, float y)
{
	operator[](3)[0] = x;
	operator[](3)[1] = y;
}

const float* yuanGL::Matrix::data() const noexcept 
{
	return &operator[](0)[0];
}
