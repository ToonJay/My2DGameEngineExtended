#pragma once

#include "EventBus/EventBus.h"
#include "Events/CollisionEvent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/TransformComponent.h"
#include <entt.hpp>
#include <spdlog.h>
#include <type_traits>

class CollisionSystem {
public:
	static void Update(std::unique_ptr<entt::registry>& registry, std::unique_ptr<EventBus>& eventBus) {
		GroundDetection(registry, eventBus);
		WallDetection(registry, eventBus);
		CeilingDetection(registry, eventBus);
	}

	static void GroundDetection(std::unique_ptr<entt::registry>& registry, std::unique_ptr<EventBus>& eventBus) {
		auto playerView = registry->view<Transform, BoxCollider, PlayerTag>();

		for (auto player : playerView) {
			auto& playerTransform = playerView.get<Transform>(player);
			auto& playerCollider = playerView.get<BoxCollider>(player);
			bool isGrounded{false};

			for (auto other : registry->view<BoxCollider>()) {
				if (other == player) {
					continue;
				}
				auto& otherTransform = registry->get<Transform>(other);
				auto& otherCollider = registry->get<BoxCollider>(other);

				isGrounded = AABBCollisionCheck(
					playerTransform.position.x + (playerCollider.offset.x + 1) * playerTransform.scale.x,
					playerTransform.position.y + playerCollider.height * playerTransform.scale.y,
					(playerCollider.width - playerCollider.offset.x - 1) * playerTransform.scale.x - 1,
					2 * playerTransform.scale.y,
					otherTransform.position.x,
					otherTransform.position.y - 2,
					otherCollider.width * otherTransform.scale.x,
					2 * otherTransform.scale.y
				);

				if (isGrounded) {
					playerCollider.isGrounded = isGrounded;
					eventBus->EmitEvent<CollisionEvent>(registry, player, other);
					break;
				}

			}
			if (!isGrounded) {
				playerCollider.isGrounded = false;
			}
		}
	}

	static void WallDetection(std::unique_ptr<entt::registry>& registry, std::unique_ptr<EventBus>& eventBus) {
		auto playerView = registry->view<Transform, BoxCollider, PlayerTag>();
	}

	static void CeilingDetection(std::unique_ptr<entt::registry>& registry, std::unique_ptr<EventBus>& eventBus) {
		auto playerView = registry->view<Transform, BoxCollider, PlayerTag>();
	}

	static bool AABBCollisionCheck(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {

		return (
			aX <= bX + bW &&
			aX + aW >= bX &&
			aY <= bY + bH &&
			aY + aH >= bY
			);
	}
};