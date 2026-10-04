#pragma once

#include <yuan_window.h>
#include <vertex_array.h>
#include <shader.h>

namespace yuanGL {

	class VertexBuffer;
	class ElementBuffer;
	class Shader;
	class Texture;

}

namespace yuanEngine {
    class World;
	class Character;
}

namespace stickman {

	class MainWindow : public yuanGL::YuanWindow {
	public:
		MainWindow();
		~MainWindow();

	private:

		virtual void inloop() override;
		virtual void resize(int width, int height) override;

		void prepare_rects();
		void prepare_man();
		void draw_rects();
		void draw_man();

	private:

		yuanEngine::World* _world;

		yuanEngine::Character* _man;

		yuanGL::VertexArray _rects_vao;
		yuanGL::VertexBuffer* _rects_vbo;
		yuanGL::ElementBuffer* _rects_ebo;

		yuanGL::VertexArray _man_vao;
		yuanGL::VertexBuffer* _man_vbo;

		yuanGL::Shader _rect_shader;
		yuanGL::Shader _man_shader;

		int _rect_indices_size{ 0 };
	};

}
