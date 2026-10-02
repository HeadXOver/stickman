#include "demo_window.h"

#include <vertex_buffer.h>
#include <element_buffer.h>
#include <vertex_array.h>
#include <vertex_attribution.h>
#include <shader.h>
#include <texture.h>
#include <matrix.h>

#include <iostream>

namespace {

    float vertices[] = {
    20.f, 20.f, 0.f, 0.f,
    980.f, 980.f, 1.f, 1.f,
    980.f, 20.f, 1.f, 0.f,
    20.f, 980.f, 0.f, 1.f
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 0, 3
    };

    float howRed = 0.f;
    float diff = 0.05f;

}

stickman::DemoWindow::DemoWindow(const char* title) :
    yuanGL::YuanWindow(title)
{
    before_draw();
}

stickman::DemoWindow::DemoWindow(int width, int height, const char* title) :
    yuanGL::YuanWindow(width, height, title)
{
    before_draw();
}

stickman::DemoWindow::~DemoWindow()
{
    delete _vao;
    delete _vbo;
    delete _ebo;
    delete _shader;
    delete _texture;
}

void stickman::DemoWindow::inloop()
{
    if (howRed > 1.f)
        diff = -0.05f;
    else if (howRed < 0.f)
        diff = 0.05f;

    howRed += diff;

    int x = 0;
    int y = 0;
    constexpr int step = 5;
    if (is_press('A')) {
        x = -step;
    }
    if (is_press('d')) {
        x = step;
    }
    if (is_press('w')) {
        y = step;
    }
    if (is_press('s')) {
        y = -step;
    }
    view_add_translate(x, y);

    _shader->set_uniform_3f("uColor", howRed, 0.3f, 0.8f);
    _shader->set_uniform_mat4("uMvp", matrix_pv());

    draw_triangles_by_elements(6);
}

void stickman::DemoWindow::resize(int width, int height)
{
}

void stickman::DemoWindow::before_draw()
{
    _vao = new yuanGL::VertexArray();
    _vbo = new yuanGL::VertexBuffer(vertices, 16);
    _ebo = new yuanGL::ElementBuffer(indices, 6);

    _vao->attach_buffer(_vbo, { 2,2 });

    _vao->attach_element_buffer(_ebo);

    _shader = new yuanGL::Shader("shader.shader");

    _vao->bind();

    _texture = new yuanGL::Texture("image/7.png");
    _texture->bind();

    _shader->set_uniform_mat4("uMvp", matrix_p());
    _shader->set_uniform_3f("uColor", howRed, 0.3f, 0.8f);
    _shader->set_uniform_i("uTexture", 0);
}
