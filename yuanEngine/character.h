#pragma once

#include "rect.h"

namespace yuanEngine {

    class Character {

    public:

        Character(float x1, float y1, float x2, float y2);

        void update();

    private:

        void record_last_position();

    private:

        Rect _box;

        float _vel_x = 0.f;
        float _vel_y = 0.f;

        float _pre_x;
        float _pre_y;

        float _friction = 0.85f;

        bool _is_grounded = false;

        float _jump_force = 12.f;
    };

}
