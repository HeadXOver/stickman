#include "demo_window.h"

#include <vertex_buffer.h>
#include <element_buffer.h>
#include <vertex_array.h>
#include <vertex_attribution.h>
#include <shader.h>
#include <texture.h>
#include <matrix.h>

namespace {

    float vertices[] = {
    20.f, 20.f, 0.f, 0.f,
    940.f, 520.f, 1.f, 1.f,
    940.f, 20.f, 1.f, 0.f,
    20.f, 520.f, 0.f, 1.f
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 0, 3
    };

    float howRed = 0.f;
    float diff = 0.05f;

}

stickman::DemoWindow::DemoWindow(int width, int height, const char* title) :
    yuanGL::YuanWindow(width, height, title)
{
    _vao = new yuanGL::VertexArray();
    _vbo = new yuanGL::VertexBuffer(vertices, 16);
    _ebo = new yuanGL::ElementBuffer(indices, 6);

    {
        yuanGL::VertexAttribution vertexAttribution({
            yuanGL::Vertex(2,4,0),
            yuanGL::Vertex(2,4,2),
            });

        _vao->attach_buffer(_vbo, vertexAttribution);
    }

    _vao->attach_element_buffer(_ebo);

    _shader = new yuanGL::Shader("shader.shader");

    _vao->bind();

    _texture = new yuanGL::Texture("image/7.png");
    _texture->bind();

    _shader->set_uniform_mat4("uMvp", matrix_p());
    _shader->set_uniform_3f("uColor", howRed, 0.3f, 0.8f);
    _shader->set_uniform_i("uTexture", 0);
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

    draw_triangles_by_elements(6);
}
