#pragma once

#include <entt.hpp>

class AnimationSystem {
public:
    static void Update(std::unique_ptr<entt::registry>& registry);
};