#pragma once

#include "rect.h"

namespace yuanEngine {

    class Character {

    public:

        Character(float x1, float y1, float x2, float y2);

        void update();

        void move_left();
        void move_right();
        void jump();

        Rect get_box() const noexcept { return _box; }

        float x() const noexcept { return _box._x; }
        float y() const noexcept { return _box._y; }

    private:

        void record_last_position();

    private:

        Rect _box;

        float _vel_x = 0.f;
        float _vel_y = 0.f;

        float _pre_x;
        float _pre_y;

        float _speed = 700.f;

        float _friction = 0.85f;

        bool _is_grounded = false;

        float _jump_force = 300.f;
    };

}
