#pragma once

struct GLFWwindow;

namespace yuanGL {

	class YuanWindow;
	class Matrix;

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

		void maximize();
		void swap_buffers() const;
		void print_gl_version() const;
		void set_swap_interval(bool v) const;
		void set_fps_limit(int limit);
		void clear() const;
		void use_3_3_core() const;
		void set_clear_color(float r, float g, float b, float a) const;
		void set_center_square(float square) noexcept { _center_square = square; }

		static void draw_triangles_by_elements(const void* data, int count);
		static void draw_triangles_by_elements(int count);

		bool should_close() const;
		bool operator!() const;

		const Matrix& matrix_p() const;

	protected:

		virtual void inloop() = 0;
		virtual void resize(int width, int height) {}

	private:

		static void before_create();

		void init_window_glew();
		void resize_update_projection(int width, int height);

	private:
		GLFWwindow* _window{ nullptr };

		Matrix* _projection{ nullptr };

		float _center_square{ 1000.0f };

		static bool _is_glfw_init;
	};

}
