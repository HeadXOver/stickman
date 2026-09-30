#pragma once

struct GLFWwindow;

namespace yuanGL {

	class Matrix;

	class YuanWindow {

	private:

		YuanWindow();
		~YuanWindow();

	public:

		void initWindow(int width, int height, const char* title);
		void initWindow(int width, int height, const char* title, GLFWwindow* share);

		YuanWindow& operator=(const YuanWindow& other) = delete;
		YuanWindow(const YuanWindow& other) = delete;

		static YuanWindow& ins();

	public:

		void make_current() const;
		void swap_buffers() const;
		void print_gl_version() const;
		void set_swap_interval(bool v) const;
		void set_fps_limit(int limit);
		void clear() const;
		void use_3_3_core() const;
		void set_clear_color(float r, float g, float b, float a) const;

		static void draw_triangles_by_elements(const void* data, int count);
		static void draw_triangles_by_elements(int count);

		bool should_close() const;
		bool operator!() const;

		const Matrix& matrix_p() const;

	private:

		void init_window_glew();

	private:
		GLFWwindow* _window{ nullptr };

		Matrix* _projection{ nullptr };
	};

}
