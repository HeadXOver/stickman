#pragma once

namespace yuanEngine {

	struct Rect {

		Rect(float x, float y, float w, float h);

		bool overlaps(const Rect& other) const;

		float _x, _y, _w, _h;
	};

}
