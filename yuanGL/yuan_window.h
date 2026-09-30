#pragma once

#include <unordered_map>

struct GLFWwindow;

namespace yuanGL {

	class Matrix;

	class YuanWindow {

	public:

		YuanWindow(int width, int height, const char* title);
		YuanWindow(int width, int height, const char* title, GLFWwindow* share);

		YuanWindow& operator=(const YuanWindow& other) = delete;
		YuanWindow(const YuanWindow& other) = delete;

		static void terminate();

	protected:

		~YuanWindow();

	public:

		void start_loop();
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

	protected:

		virtual void inloop() = 0;
		virtual void resize(int width, int height) {}

	private:

		static void before_create();

		void init_window_glew();

	private:
		GLFWwindow* _window{ nullptr };

		Matrix* _projection{ nullptr };

		static bool _is_glfw_init;

		static std::unordered_map<GLFWwindow*, YuanWindow*> _hash_window;
	};

}
