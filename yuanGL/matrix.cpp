#include "pch.h"
#include "matrix.h"

yuanGL::Matrix::Matrix() :
	_type(MatrixType::Identity)
{
	_m = new glm::mat4(1.f);
}

yuanGL::Matrix::Matrix(float s) :
	_type((s == 1.f) ? MatrixType::Identity : MatrixType::Homo)
{
	_m = new glm::mat4(s);
}

yuanGL::Matrix::Matrix(const glm::mat4& m) :
	_type(MatrixType::None)
{
	_m = new glm::mat4(m);
}

yuanGL::Matrix::Matrix(MatrixType type, float f1, float f2, float f3, float f4)
{
	switch (type) {
	case MatrixType::Ortho:
		*_m = glm::ortho(f1, f2, f3, f4, -1.f, 1.f);
		_type = MatrixType::Ortho;
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
		*_m = glm::ortho(f1, f2, f3, f4, f5, f6);
		_type = MatrixType::Ortho;
		break;
	default:
		std::cout << "Error: MatrixType not supported" << std::endl;
		__debugbreak();
	}
}

yuanGL::Matrix::~Matrix()
{
	delete _m;
}

void yuanGL::Matrix::set_to_orth(float left, float right, float bottom, float top)
{
	*_m = glm::ortho(left, right, bottom, top, -1.f, 1.f);
	_type = MatrixType::Ortho;
}

const float* yuanGL::Matrix::data() const noexcept {
	return &(*_m)[0][0];
}
