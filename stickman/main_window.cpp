#include "main_window.h"

#include <vector>

#include <world.h>

#include <vertex_buffer.h>
#include <element_buffer.h>

stickman::MainWindow::MainWindow() :
	yuanGL::YuanWindow("stickman"),
	_rect_shader("pos2_color4_simple.shader"),
	_world(new yuanEngine::World(1000.f, 1000.f))
{
	regist_resize_shader(_rect_shader);

	std::vector<float> rectbuffer;
	std::vector<unsigned int> rectIndices;

	_world->get_rect_buffers(rectbuffer, rectIndices);

	_rect_indices_size = static_cast<int>(rectIndices.size());

	_rects_vbo = new yuanGL::VertexBuffer(rectbuffer.data(), (unsigned int)rectbuffer.size());
	_rects_ebo = new yuanGL::ElementBuffer(rectIndices.data(), (unsigned int)rectIndices.size());

	_rects_vao.attach_buffer(_rects_vbo, { 2, 4 });
	_rects_vao.attach_element_buffer(_rects_ebo);

	_rect_shader.set_uniform_mat4("uMvp", matrix_pv());
}

stickman::MainWindow::~MainWindow()
{
	delete _world;
	delete _rects_vbo;
	delete _rects_ebo;
}

void stickman::MainWindow::inloop()
{
	_rects_vao.bind();
	_rect_shader.bind();

	draw_triangles_by_elements(_rect_indices_size);
}

void stickman::MainWindow::resize(int width, int height)
{
}
