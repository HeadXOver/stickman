#pragma once

#include <vector>

#include "rect.h"

namespace yuanEngine {

	class World {

	public:

		World(float width, float height);

		float width() const noexcept { return _width; }
		float height() const noexcept { return _height; }
		float gravity() const noexcept { return _gravity; }

		void set_gravity(float gravity) noexcept { _gravity = gravity; }

		void get_rect_buffers(std::vector<float>& vertices, std::vector<unsigned int>& indices);

		const std::vector<yuanEngine::Rect>& rects() const noexcept { return _rects; }

	public:

		float _gravity = 0.6f;

	private:

		float _width;
		float _height;

		std::vector<yuanEngine::Rect> _rects;
	};

}
