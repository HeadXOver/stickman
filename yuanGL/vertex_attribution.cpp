#include "pch.h"
#include "vertex_attribution.h"

#include "gl_call.h"

yuanGL::VertexAttribution::VertexAttribution(std::initializer_list<Vertex> init_list)
{
    _attributions = init_list;
}

yuanGL::VertexAttribution::~VertexAttribution()
{
}

void yuanGL::VertexAttribution::enable() const
{
    for (int i = 0; i < _attributions.size(); i++) {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, _attributions[i]._degree, GL_FLOAT, GL_FALSE, _attributions[i]._split * sizeof(float), (void*)(_attributions[i]._skew * sizeof(float))));
    }
}
