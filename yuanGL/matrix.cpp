#include "pch.h"
#include "matrix.h"

yuanGL::Matrix::Matrix() :
	glm::mat4(1.f),
	_type(MatrixType::Identity)
{

}

yuanGL::Matrix::Matrix(float s) :
	glm::mat4(s),
	_type((s == 1.f) ? MatrixType::Identity : MatrixType::Homo)
{

}

yuanGL::Matrix::Matrix(const glm::mat4& m) :
	glm::mat4(m),
	_type(MatrixType::None)
{
}

yuanGL::Matrix::Matrix(MatrixType type, float f1, float f2, float f3, float f4)
{
	switch (type) {
	case MatrixType::Ortho:
		*this = glm::ortho(f1, f2, f3, f4, -1.f, 1.f);
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
		*this = glm::ortho(f1, f2, f3, f4, f5, f6);
		_type = MatrixType::Ortho;
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
