#include "main_window.h"

#include <vector>

#include <world.h>
#include <scene.h>
#include <character.h>

#include <vertex_buffer.h>
#include <element_buffer.h>

stickman::MainWindow::MainWindow() :
	yuanGL::YuanWindow("stickman"),
	_rect_shader("pos2_color4_simple.shader"),
	_man_shader("pos2_color4_upos.shader"),
	_world(new yuanEngine::World(1000.f, 1000.f)),
	_man(new yuanEngine::Character(10.f, 10.f, 100.f, 177.f))
{
	yuanEngine::Scene::get_instance().set_world(_world);
	regist_resize_shader(_rect_shader);
	regist_resize_shader(_man_shader);

	prepare_rects();
	prepare_man();
}

stickman::MainWindow::~MainWindow()
{
	delete _world;
	delete _rects_vbo;
	delete _rects_ebo;
	delete _man_vbo;
}

void stickman::MainWindow::inloop()
{
	if(is_press('a')) _man->move_left();
	if (is_press('d')) _man->move_right();
	if (is_press('w')) _man->jump();
	_man->update();
	draw_rects();
	draw_man();
}

void stickman::MainWindow::resize(int width, int height)
{
}

void stickman::MainWindow::prepare_rects()
{
	std::vector<float> rectbuffer;
	std::vector<unsigned int> rectIndices;

	_world->get_rect_buffers(rectbuffer, rectIndices);

	_rect_indices_size = static_cast<int>(rectIndices.size());

	_rects_vbo = new yuanGL::VertexBuffer(rectbuffer.data(), (unsigned int)rectbuffer.size());
	_rects_ebo = new yuanGL::ElementBuffer(rectIndices.data(), (unsigned int)rectIndices.size());

	_rects_vao.attach_buffer(_rects_vbo, { 2, 4 });
	_rects_vao.attach_element_buffer(_rects_ebo);
}

void stickman::MainWindow::prepare_man()
{
	yuanEngine::Rect manRect = _man->get_box();

	float manbuffer[] = {
		0.f, 0.f, 0.7f, 0.2f, 0.1f, 1.f,
		manRect._w, 0.f, 0.7f, 0.2f, 0.1f, 1.f,
		manRect._w, manRect._h, 0.7f, 0.2f, 0.1f, 1.f,
		0.f, manRect._h, 0.7f, 0.2f, 0.1f, 1.f
	};

	_man_vbo = new yuanGL::VertexBuffer(manbuffer, 24);
	_man_vao.attach_buffer(_man_vbo, { 2, 4 });
}

void stickman::MainWindow::draw_rects()
{
	_rects_vao.bind();
	_rect_shader.bind();

	draw_triangles_by_elements(_rect_indices_size);
}

void stickman::MainWindow::draw_man()
{
	_man_vao.bind();
	_man_shader.bind();

	_man_shader.set_uniform_2f("uOffset", _man->x(), _man->y());
	draw_rects_by_buffer(1);
}
