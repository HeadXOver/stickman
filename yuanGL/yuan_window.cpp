#include "pch.h"

#include "yuan_window.h"
#include "gl_call.h"
#include "matrix.h"

bool yuanGL::YuanWindow::_is_glfw_init = false;

yuanGL::YuanWindow::YuanWindow(int width, int height, const char* title)
{
	before_create();
	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	init_window_glew();
	_projection = new Matrix(MatrixType::Ortho, 0.f, 960.f, 0.f, 540.f);
}

yuanGL::YuanWindow::YuanWindow(int width, int height, const char* title, GLFWwindow* share)
{
	before_create();
	_window = glfwCreateWindow(width, height, title, NULL, share);
	init_window_glew();
	_projection = new Matrix(MatrixType::Ortho, 0.f, 960.f, 0.f, 540.f);
}

yuanGL::YuanWindow::~YuanWindow()
{
	glfwDestroyWindow(_window);
	delete _projection;
}

void yuanGL::YuanWindow::terminate()
{
	glfwTerminate();
}

void yuanGL::YuanWindow::start_loop(LoopFunc func)
{
	while (!should_close())
	{
		clear();

		func();

		swap_buffers();

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void yuanGL::YuanWindow::make_current() const
{
	glfwMakeContextCurrent(_window);
}

void yuanGL::YuanWindow::swap_buffers() const
{
	glfwSwapBuffers(_window);
}

void yuanGL::YuanWindow::print_gl_version() const
{
	std::cout << glGetString(GL_VERSION) << std::endl;
}

void yuanGL::YuanWindow::set_swap_interval(bool v) const
{
	glfwSwapInterval(v ? 1 : 0);
}

void yuanGL::YuanWindow::set_fps_limit(int limit)
{
	glfwSwapInterval(0);
}

void yuanGL::YuanWindow::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void yuanGL::YuanWindow::use_3_3_core() const
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void yuanGL::YuanWindow::set_clear_color(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

void yuanGL::YuanWindow::draw_triangles_by_elements(const void* data, int count)
{
	GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, data));
}

void yuanGL::YuanWindow::draw_triangles_by_elements(int count)
{
	GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0));
}

bool yuanGL::YuanWindow::should_close() const
{
	return glfwWindowShouldClose(_window);
}

bool yuanGL::YuanWindow::operator!() const {
	return !_window;
}

const yuanGL::Matrix& yuanGL::YuanWindow::matrix_p() const
{
	return *_projection;
}

void yuanGL::YuanWindow::before_create()
{
	if (!_is_glfw_init) {
		if (!glfwInit()) {
			std::cout << "Failed to initialize GLFW" << std::endl;
			__debugbreak();
			exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
}

void yuanGL::YuanWindow::init_window_glew()
{
	if (!_window) {
		__debugbreak();
	}

	make_current();

	if (glewInit() != GLEW_OK) {
		__debugbreak();
	}

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}
