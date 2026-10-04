#include "pch.h"
#include "rect.h"

yuanEngine::Rect::Rect(float x, float y, float w, float h) :
	_x(x), _y(y), _w(w), _h(h)
{
}

bool yuanEngine::Rect::overlaps(const Rect& other) const
{
	return
		_x < other._x + other._w && _x + _w > other._x &&
		_y < other._y + other._h && _y + _h > other._y;
}
