#pragma once

#include <list>

struct GLFWwindow;

namespace yuanGL {

	class YuanWindow;
	class Matrix;
	class Transformer;
	class Shader;

	using ResizeFunc = void (YuanWindow::*)(int, int);

	class YuanWindow {

		friend void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	public:

		YuanWindow(const char* title = "untitled");
		YuanWindow(int width, int height, const char* title);
		YuanWindow(int width, int height, const char* title, GLFWwindow* share);

		YuanWindow& operator=(const YuanWindow& other) = delete;
		YuanWindow(const YuanWindow& other) = delete;

		static void terminate();

	protected:

		~YuanWindow();

	public:

		void start_loop();
		void start_loop_fps(int fps);

		void view_add_translate(float x, float y);
		void view_set_position(float x, float y);
		void view_set_scale(float x);
		void view_add_scale(float x);

		void maximize();
		void swap_buffers() const;
		void print_gl_version() const;
		void set_swap_interval(bool v) const;
		void clear() const;
		void use_3_3_core() const;
		void set_clear_color(float r, float g, float b, float a) const;
		void set_center_square(float square) noexcept { _center_square = square; }

		static void draw_triangles_by_elements(const void* data, int count);
		static void draw_triangles_by_elements(int count);

		bool should_close() const;
		bool operator!() const;

		bool is_press(char key) const;

		const Matrix& matrix_p() const;
		const Matrix& matrix_pv() const;

	protected:

		virtual void inloop() = 0;
		virtual void resize(int width, int height) {}

		void regist_resize_shader(Shader& shader);
		void unregist_resize_shader(Shader& shader);

	private:

		static void before_create();

		void init_window_glew();
		void resize_update_projection(int width, int height);
		void update_pv_matrix();

		void init();

	private:
		GLFWwindow* _window{ nullptr };

		Matrix* _projection{ nullptr };
		Matrix* _view{ nullptr };
		Matrix* _matrix_pv{ nullptr };

		Transformer* _view_transformer{ nullptr };

		float _center_square{ 1000.0f };

		static bool _is_glfw_init;

		std::list<Shader*> _resize_shaders;
	};

}
