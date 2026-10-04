#pragma once

namespace yuanEngine {

    class World;

    class Scene {

    private:

        Scene();
        ~Scene() = default;

    public:

        static Scene& get_instance();

        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;

        World* world() noexcept { return _world; }

        void set_world(World* world) noexcept { _world = world; }
        void set_delta_time(float delta_time) noexcept { _delta_time = delta_time; }
        float delta_time() const noexcept { return _delta_time; }

    private:

        World* _world{ nullptr };

        float _delta_time = 1.f / 120.f;
    };

}
