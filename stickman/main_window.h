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
}

namespace stickman {

	class MainWindow : public yuanGL::YuanWindow {
	public:
		MainWindow();
		~MainWindow();

	private:

		virtual void inloop() override;
		virtual void resize(int width, int height) override;

	private:

		yuanEngine::World* _world;

		yuanGL::VertexArray _rects_vao;
		yuanGL::VertexBuffer* _rects_vbo;
		yuanGL::ElementBuffer* _rects_ebo;

		yuanGL::Shader _rect_shader;

		int _rect_indices_size{ 0 };
	};

}
