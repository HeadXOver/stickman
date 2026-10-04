#include "pch.h"
#include "character.h"
#include "world.h"
#include "scene.h"

yuanEngine::Character::Character(float x1, float y1, float x2, float y2) :
	_box(x1, y1, x2, y2),
	_pre_x(x1),
	_pre_y(y1)
{
}

void yuanEngine::Character::update()
{
    record_last_position();

    Scene& scene = Scene::get_instance();
    World* world = scene.world();
    const float deltaTime = scene.delta_time();
    const float gravity = world->gravity();
    const float worldWidth = world->width();

    // 应用重力
    if (!_is_grounded) {
        _vel_y += gravity * deltaTime;
    }

    // X轴 : 水平移动与碰撞检测
    _box._x += _vel_x * deltaTime;

    if (_box._x < 0.0f) {
        _box._x = 0.0f;
        _vel_x = 0.0f;
    }
    else if (_box._x + _box._w > worldWidth) {
        _box._x = worldWidth - _box._w;
        _vel_x = 0.0f;
    }

    for (const auto& eachRect : world->rects()) {
        if (_box.overlaps(eachRect)) {
            // 发生水平碰撞，根据速度方向将玩家“推”出墙体
            if (_vel_x > 0) {
                // 向右撞：推到墙的左边
                _box._x = eachRect._x - _box._w;
            }
            else if (_vel_x < 0) {
                // 向左撞：推到墙的右边
                _box._x = eachRect._x + eachRect._w;
            }
            _vel_x = 0; // 撞墙后水平速度清零
        }
    }

    // Z轴 : 垂直移动与碰撞检测
    _box._y += _vel_y * deltaTime;
    _is_grounded = false; // 默认假设在空中

    if (_box._y < 0.0f) {
        _box._y = 0.0f;
        _vel_y = 0.0f;
        _is_grounded = true;
    }
    else if (_box._y + _box._h > world->height()) {
        _box._y = world->height() - _box._h;
        _vel_y = 0.0f;
    }

    for (const auto& eachRect : world->rects()) {
        if (_box.overlaps(eachRect)) {
            if (_vel_y < 0) {
                // 向下运动（落地）：推到墙的上面
                _box._y = eachRect._y + eachRect._h;
                _is_grounded = true;
                _vel_y = 0; // 落地后垂直速度清零
            }
            else if (_vel_y > 0) {
                // 向上运动（顶天花板）：推到墙的下面
                _box._y = eachRect._y - _box._h;
                _vel_y = 0;
            }
        }
    }

    // 摩擦力处理 (仅在地面时生效)
    if (_is_grounded) {
        _vel_x *= _friction;
        if (std::abs(_vel_x) < 0.1f) _vel_x = 0.0f;
    }
}

void yuanEngine::Character::record_last_position()
{
    _pre_x = _box._x;
    _pre_y = _box._y;
}
