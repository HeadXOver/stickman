#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <yuan_window.h>
#include <vertex_buffer.h>
#include <element_buffer.h>
#include <vertex_array.h>
#include <vertex_attribution.h>
#include <shader.h>
#include <texture.h>
#include <matrix.h>

#include <iostream>
#include <string>

#pragma region [variales]

yuanGL::YuanWindow* pWindow = nullptr;

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

#pragma endregion

void update()
{
    if (howRed > 1.f)
        diff = -0.05f;
    else if (howRed < 0.f)
        diff = 0.05f;

    howRed += diff;

    pWindow->draw_triangles_by_elements(6);
}

int main(void)
{
    {
        yuanGL::YuanWindow window(960, 540, "stickman");

        pWindow = &window;

        window.print_gl_version();
        window.set_swap_interval(true);
        yuanGL::VertexArray vertexArray;
        yuanGL::VertexBuffer buffer(vertices, 16);
        yuanGL::ElementBuffer idBuffer(indices, 6);

        {
            yuanGL::VertexAttribution vertexAttribution({
                yuanGL::Vertex(2,4,0),
                yuanGL::Vertex(2,4,2),
                });

            vertexArray.attach_buffer(buffer, vertexAttribution);
        }

        vertexArray.attach_element_buffer(idBuffer);

        yuanGL::Shader shader("shader.shader");

        window.set_clear_color(howRed, 0.3f, 0.8f, 1.0f);

        vertexArray.bind();

        yuanGL::Texture texture("image/7.png");
        texture.bind();

        shader.set_uniform_mat4("uMvp", window.matrix_p());
        shader.set_uniform_3f("uColor", howRed, 0.3f, 0.8f);
        shader.set_uniform_i("uTexture", 0);

        window.start_loop(update);
    }

    yuanGL::YuanWindow::terminate();
}