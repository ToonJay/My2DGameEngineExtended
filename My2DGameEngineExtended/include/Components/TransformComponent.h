#pragma once
#include <glm.hpp>

struct TransformComponent {
    glm::vec2 position{0, 0};
    glm::vec2 scale{1, 1};   

    TransformComponent() = default;

    TransformComponent(const glm::vec2& position, const glm::vec2& scale)
        : position{position}, scale{scale} {}
};
using Transform = TransformComponent;