#include "pch.h"

#include "yuan_window.h"
#include "gl_call.h"
#include "matrix.h"
#include "yuanGL.h"
#include "transformer.h"
#include "shader.h"

namespace {

	std::unordered_map<GLFWwindow*, yuanGL::YuanWindow*> hashWindow;

}

namespace yuanGL {

	void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		auto findWindow = hashWindow.find(window);
		if (findWindow != hashWindow.end()) {
			findWindow->second->resize_update_projection(width, height);
			findWindow->second->resize(width, height);
		}
	}

}

bool yuanGL::YuanWindow::_is_glfw_init = false;

yuanGL::YuanWindow::YuanWindow(const char* title)
{
	init();
	before_create();
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	_window = glfwCreateWindow(1080, 720, title, NULL, NULL);
	init_window_glew();
	maximize();
	glfwShowWindow(_window);
}

yuanGL::YuanWindow::YuanWindow(int width, int height, const char* title)
{
	init();
	before_create();
	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	init_window_glew();
	resize_update_projection(width, height);
}

yuanGL::YuanWindow::YuanWindow(int width, int height, const char* title, GLFWwindow* share)
{
	init();
	before_create();
	_window = glfwCreateWindow(width, height, title, NULL, share);
	init_window_glew();
	resize_update_projection(width, height);
}

yuanGL::YuanWindow::~YuanWindow()
{
	glfwDestroyWindow(_window);
	hashWindow.erase(_window);
	delete _projection;
	delete _view;
}

void yuanGL::YuanWindow::terminate()
{
	glfwTerminate();
}

void yuanGL::YuanWindow::start_loop()
{
	while (!should_close())
	{
		clear();

		inloop();

		swap_buffers();

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void yuanGL::YuanWindow::start_loop_fps(int fps)
{
	const float deltaTime = 1.0f / fps;

	glfwSwapInterval(0);

	while (!should_close())
	{
		double frameStart = glfwGetTime();

		clear();

		inloop();

		swap_buffers();

		/* Poll for and process events */
		glfwPollEvents();

		double frameEnd = glfwGetTime();
		double elapsed = frameEnd - frameStart;
		double remaining = deltaTime - elapsed;

		if (remaining > 0.0)
		{
			// 先 sleep 掉大部分时间，降低 CPU 占用
			if (remaining > 0.002)
			{
				std::this_thread::sleep_for(
					std::chrono::duration<double>(remaining - 0.002)
				);
			}

			// 最后 2ms 左右忙等，提高精度
			while (glfwGetTime() - frameStart < deltaTime)
			{
				// 空转等待
			}
		}
	}
}

void yuanGL::YuanWindow::view_add_translate(float x, float y)
{
	_view->add_translate(-x, -y);
	_view_transformer->add_translate(-x, -y);
	update_pv_matrix();
}

void yuanGL::YuanWindow::view_set_position(float x, float y)
{
	_view->set_translate(-x, -y);
	_view_transformer->set_translate(-x, -y);
	update_pv_matrix();
}

void yuanGL::YuanWindow::view_set_scale(float x)
{
	float currentS = _view_transformer->w();
	view_add_scale(x / currentS);
}

void yuanGL::YuanWindow::view_add_scale(float x)
{
	const float oneMointX = 1.f - x;
	const float s = _center_square * _view_transformer->w() * 0.5f;
	float sx = (_view_transformer->x() + s) * oneMointX;
	float sy = (_view_transformer->y() + s) * oneMointX;
	_view_transformer->set_translate(sx, sy);
	_view_transformer->add_scale(x);
	*_view = *_view_transformer;
	update_pv_matrix();
}

void yuanGL::YuanWindow::update_pv_matrix()
{
	(*_matrix_pv) = (*_projection) * (*_view);
	for (auto& shader : _resize_shaders) {
		shader->set_uniform_mat4("uMvp", *_matrix_pv);
	}
}

void yuanGL::YuanWindow::regist_resize_shader(Shader& shader)
{
	_resize_shaders.push_back(&shader);
}

void yuanGL::YuanWindow::unregist_resize_shader(Shader& shader)
{
	_resize_shaders.remove(&shader);
}

void yuanGL::YuanWindow::init()
{
	_projection = new Matrix();
	_view = new Matrix();
	_matrix_pv = new Matrix();
	_view_transformer = new Transformer();
}

void yuanGL::YuanWindow::maximize()
{
	glfwMaximizeWindow(_window);
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

bool yuanGL::YuanWindow::is_press(char key) const
{
	// 转成大写，兼容 'a'/'A' 两种写法
	char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(key)));

	if (upper < 'A' || upper > 'Z') {
		int glfw_key = char_to_glfw_key(key);
		return glfwGetKey(_window, glfw_key) == GLFW_PRESS;
	}


	int glfw_key = GLFW_KEY_A + (upper - 'A');

	return glfwGetKey(_window, glfw_key) == GLFW_PRESS;
}

const yuanGL::Matrix& yuanGL::YuanWindow::matrix_p() const
{
	return *_projection;
}

const yuanGL::Matrix& yuanGL::YuanWindow::matrix_pv() const
{
	return *_matrix_pv;
}

void yuanGL::YuanWindow::before_create()
{
	if (!_is_glfw_init) {
		if (!glfwInit()) {
			std::cout << "Failed to initialize GLFW" << std::endl;
			__debugbreak();
			exit(EXIT_FAILURE);
		}

		_is_glfw_init = true;

		glfwSwapInterval(1);

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

	hashWindow[_window] = this;

	glfwMakeContextCurrent(_window);

	if (glewInit() != GLEW_OK) {
		__debugbreak();
	}

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
}

void yuanGL::YuanWindow::resize_update_projection(int width, int height)
{
	if (width > height) {
		const float over = ((width - height) >> 1) * _center_square / height;
		_projection->set_to_orth(-over, _center_square + over, 0.f, _center_square);
	}
	else if (width < height) {
		const float over = ((height - width) >> 1) * _center_square / width;
		_projection->set_to_orth(0.f, _center_square, -over, _center_square + over);
	}
	else {
		_projection->set_to_orth(0.f, _center_square, 0.f, _center_square);
	}

	update_pv_matrix();
}
