#pragma once
#pragma once
#include <glm.hpp>

struct BoxColliderComponent {
	int width{0};
	int height{0};
	glm::vec2 offset{0, 0};
	bool isGrounded{false};
	bool isTouchingWall{false};
	bool isTouchingCeiling{false};

	BoxColliderComponent() = default;

	BoxColliderComponent(const int width, const int height, const glm::vec2& offset)
		: width{width}, height{height}, offset{offset} {}
};
using BoxCollider = BoxColliderComponent;