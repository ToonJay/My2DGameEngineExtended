#pragma once

#include <glm.hpp>

struct RigidBodyComponent {
	int speed{0};
	int jumpSpeed{0};
	int fallSpeed{0};
	glm::vec2 velocity{0, 0};
	bool gravityEnabled{true};
	glm::vec2 accumulatedMovement{0.0, 0.0};

	RigidBodyComponent() = default;

	RigidBodyComponent(const int speed, const int jumpSpeed, const int fallSpeed, const glm::vec2& velocity, const bool gravityEnabled)
		: speed{speed}, jumpSpeed{jumpSpeed}, fallSpeed{fallSpeed}, velocity {velocity}, gravityEnabled{gravityEnabled} {}
};
using RigidBody = RigidBodyComponent;