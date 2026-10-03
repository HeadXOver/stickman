#pragma once

namespace yuanGL {

    class Matrix;

    class Transformer {

    public:

        Transformer() {}
        Transformer(float x, float y, float w, float h, float r);

        void add_translate(float x, float y) noexcept {
            _x += x;
            _y += y;
        }

        void set_translate(float x, float y) noexcept {
            _x = x;
            _y = y;
        }

        void add_scale(float s) noexcept {
            _w *= s;
            _h *= s;
        }

        void add_scale_after_translate(float s) noexcept {
            _w *= s;
            _h *= s;
            _x *= s;
            _y *= s;
        }

        void set_scale(float s) noexcept {
            _w = s;
            _h = s;
        }

        void add_scale(float w, float h) noexcept {
            _w *= w;
            _h *= h;
        }

        void set_scale(float w, float h) noexcept {
            _w = w;
            _h = h;
        }

        float x() const { return _x; }
        float y() const { return _y; }
        float w() const { return _w; }
        float h() const { return _h; }
        float r() const { return _r; }

    private:

        float _x{ 0.f };
        float _y{ 0.f };
        float _w{ 1.f };
        float _h{ 1.f };
        float _r{ 0.f };
    };

}
