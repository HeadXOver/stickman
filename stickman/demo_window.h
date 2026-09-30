#pragma once

#include <yuan_window.h>

namespace yuanGL {

    class VertexArray;
    class VertexBuffer;
    class ElementBuffer;
    class Shader;
    class Texture;

}

namespace stickman {

    class DemoWindow final : public yuanGL::YuanWindow {

    public:
        DemoWindow(int width, int height, const char* title);
        ~DemoWindow();

    private:

        virtual void inloop() override;

    private:

        yuanGL::VertexArray* _vao;
        yuanGL::VertexBuffer* _vbo;
        yuanGL::ElementBuffer* _ebo;

        yuanGL::Shader* _shader;

        yuanGL::Texture* _texture;
    };

}
