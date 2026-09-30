#include "pch.h"
#include "vertex_array.h"

#include "gl_call.h"
#include "vertex_buffer.h"
#include "element_buffer.h"
#include "vertex_attribution.h"

yuanGL::VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &_id));
}

yuanGL::VertexArray::~VertexArray()
{
    this->unbind();
    GLCall(glDeleteVertexArrays(1, &_id));
}

void yuanGL::VertexArray::attach_buffer(const VertexBuffer& vb, const VertexAttribution& attribution)
{
    this->bind();
    vb.bind();
    attribution.enable();
    this->unbind();
    vb.unbind();
}

void yuanGL::VertexArray::attach_buffer(const VertexBuffer* vb, const VertexAttribution& attribution)
{
    this->bind();
    vb->bind();
    attribution.enable();
    this->unbind();
    vb->unbind();
}

void yuanGL::VertexArray::attach_element_buffer(const ElementBuffer& eb)
{
    this->bind();
    eb.bind();
    this->unbind();
    eb.unbind();
}

void yuanGL::VertexArray::attach_element_buffer(const ElementBuffer* eb)
{
    this->bind();
    eb->bind();
    this->unbind();
    eb->unbind();
}

void yuanGL::VertexArray::bind() const
{
    GLCall(glBindVertexArray(_id));
}

void yuanGL::VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}
