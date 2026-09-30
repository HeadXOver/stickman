#include "pch.h"
#include "vertex_buffer.h"

#include "yuan_enum.h"
#include "gl_call.h"

yuanGL::VertexBuffer::VertexBuffer(float* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &_id));
    this->bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW));
    this->unbind();
}

yuanGL::VertexBuffer::VertexBuffer(float* data, unsigned int size, DrawMode drawMode)
{
    GLCall(glGenBuffers(1, &_id));
    this->bind();
    unsigned int drawModeGL = GL_STATIC_DRAW;
    switch (drawMode) {
    case yuanGL::DrawMode::Dynamic:
        drawModeGL = GL_DYNAMIC_DRAW;
        break;
    case yuanGL::DrawMode::Stream:
        drawModeGL = GL_STREAM_DRAW;
        break;
    }

    GLCall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, drawModeGL));
    this->unbind();
}

yuanGL::VertexBuffer::~VertexBuffer()
{
    this->unbind();
    GLCall(glDeleteBuffers(1, &_id));
}

void yuanGL::VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _id));
}

void yuanGL::VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}