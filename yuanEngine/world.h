#pragma once

#include <vector>

#include "rect.h"

namespace yuanEngine {

	class World {

	public:

		World(float width, float height);

	private:

		float _width;
		float _height;

		std::vector<yuanEngine::Rect> _rects;
	};

}
