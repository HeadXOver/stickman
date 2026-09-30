#include "pch.h"
#include "element_buffer.h"

#include "yuan_enum.h"
#include "gl_call.h"

yuanGL::ElementBuffer::ElementBuffer(unsigned int* indices, unsigned int count)
{
    GLCall(glGenBuffers(1, &_id));
    this->bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
    this->unbind();
}

yuanGL::ElementBuffer::ElementBuffer(unsigned int* indices, unsigned int count, DrawMode mode)
{
    GLCall(glGenBuffers(1, &_id));
    this->bind();

    unsigned int drawModeGL = GL_STATIC_DRAW;
    switch (mode) {
    case yuanGL::DrawMode::Dynamic:
        drawModeGL = GL_DYNAMIC_DRAW;
        break;
    case yuanGL::DrawMode::Stream:
        drawModeGL = GL_STREAM_DRAW;
        break;
    }

    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, drawModeGL));
    this->unbind();
}

void yuanGL::ElementBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void yuanGL::ElementBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

yuanGL::ElementBuffer::~ElementBuffer()
{
    this->unbind();
    GLCall(glDeleteBuffers(1, &_id));
}
