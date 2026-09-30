#pragma once

namespace yuanGL {

    enum class DrawMode;

    class ElementBuffer {

    public:
        ElementBuffer(unsigned int* indices, unsigned int count);
        ElementBuffer(unsigned int* indices, unsigned int count, DrawMode mode);
        ~ElementBuffer();

        void bind() const;
        void unbind() const;

    private:

        unsigned int _id{ 0u };
    };

}
