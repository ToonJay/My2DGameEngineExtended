#pragma once

#include <glm.hpp>

struct RigidBodyComponent {
	float speed{0};
	glm::vec2 velocity{0.0f, 0.0f};
	bool gravityEnabled{true};

	RigidBodyComponent() = default;

	RigidBodyComponent(const float speed, const glm::vec2& velocity, const bool gravityEnabled)
		: speed{speed}, velocity{velocity}, gravityEnabled{gravityEnabled} {}
};
using RigidBody = RigidBodyComponent;