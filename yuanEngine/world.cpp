#include "pch.h"
#include "world.h"

yuanEngine::World::World(float width, float height) :
	_width(width),
	_height(height)
{
	_rects.emplace_back(0.5f * width, 0.5f * _height, _width, _height);
}

void yuanEngine::World::get_rect_buffers(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	vertices.clear();
	indices.clear();

    vertices.reserve(_rects.size() * 24);
	indices.reserve(_rects.size() * 6);

    float oneRectVertex[] = {
        0.0f, 0.0f, 1.f, 1.f, 1.f, 1.f,
        _width, 0.0f, 1.f, 1.f, 1.f, 1.f,
        _width, _height, 1.f, 1.f, 1.f, 1.f,
        0.0f, _height, 1.f, 1.f, 1.f, 1.f
    };

    unsigned int oneRectIndices[] = {
        0, 1, 2,
        2, 3, 0
    };

    vertices.insert(vertices.end(), oneRectVertex, oneRectVertex + 24);
    indices.insert(indices.end(), oneRectIndices, oneRectIndices + 6);

    for (auto& rect : _rects) {                                        
    }
}
