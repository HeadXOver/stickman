#pragma once

#include <vector>

#include "rect.h"

namespace yuanEngine {

	class World {

	public:

		World(float width, float height);

		void get_rect_buffers(std::vector<float>& vertices, std::vector<unsigned int>& indices);

	private:

		float _width;
		float _height;

		std::vector<yuanEngine::Rect> _rects;
	};

}
