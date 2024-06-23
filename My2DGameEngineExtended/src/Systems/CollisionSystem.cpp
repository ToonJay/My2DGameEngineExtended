#include "Systems/CollisionSystem.h"

#include "Events/CollisionEvent.h"
#include "EventBus/EventBus.h"
#include "Components/BoxColliderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Utilities/Rect.h"
#include <spdlog.h>

void CollisionSystem::Update(std::unique_ptr<entt::registry>& registry, std::unique_ptr<EventBus>& eventBus) {
	auto view = registry->view<RigidBody, Transform, BoxCollider>();

	bool isGrounded{false};
	bool isTouchingLeftWall{false};
	bool isTouchingRightWall{false};
	bool isTouchingCeiling{false};

	for (auto a : view) {
		auto& aTransform = view.get<Transform>(a);
		auto& aCollider = view.get<BoxCollider>(a);
		isGrounded = false;
		isTouchingLeftWall = false;
		isTouchingRightWall = false;
		isTouchingCeiling = false;

		for (auto b : registry->view<Transform, BoxCollider>()) {
			if (b == a) {
				continue;
			}
			auto& bTransform = registry->get<Transform>(b);
			auto& bCollider = registry->get<BoxCollider>(b);

			CollisionType collisionType = CheckCollision(aTransform, aCollider, bTransform, bCollider);

			if (collisionType != CollisionType::None) {
				switch (collisionType) {
				case CollisionType::Ceiling:
					isTouchingCeiling = true;
					break;
				case CollisionType::Ground:
					isGrounded = true;
					break;
				case CollisionType::Left:
					isTouchingLeftWall = true;
					break;
				case CollisionType::Right:
					isTouchingRightWall = true;
					break;
				default:
					break;
				}
				eventBus->EmitEvent<CollisionEvent>(registry, a, b, collisionType);
			}
		}

		aCollider.isGrounded = isGrounded;
		aCollider.isTouchingLeftWall = isTouchingLeftWall;
		aCollider.isTouchingRightWall = isTouchingRightWall;
		aCollider.isTouchingCeiling = isTouchingCeiling;
	}
}

CollisionType CollisionSystem::CheckCollision(const Transform& aTransform, const BoxCollider& aCollider, const Transform& bTransform, const BoxCollider& bCollider) {
	Rect aBottomRect{
		aTransform.position.x + aCollider.offset.x * aTransform.scale.x,
		aTransform.position.y + (aCollider.height + aCollider.offset.y) * aTransform.scale.y,
		aCollider.width * aTransform.scale.x,
		2 * aTransform.scale.y
	};
	Rect aTopRect{
		aTransform.position.x + aCollider.offset.x * aTransform.scale.x,
		aTransform.position.y + (aCollider.offset.y - 2) * aTransform.scale.y,
		aCollider.width * aTransform.scale.x,
		2 * aTransform.scale.y
	};
	Rect aRightRect{
		aTransform.position.x + (aCollider.width + aCollider.offset.x) * aTransform.scale.x,
		aTransform.position.y + aCollider.offset.y * aTransform.scale.y,
		2 * aTransform.scale.x,
		aCollider.height * aTransform.scale.y
	};
	Rect aLeftRect{
		aTransform.position.x + (aCollider.offset.x - 2) * aTransform.scale.x,
		aTransform.position.y + aCollider.offset.y * aTransform.scale.y,
		2 * aTransform.scale.x,
		aCollider.height * aTransform.scale.y
	};
	Rect bRect{
		bTransform.position.x + bCollider.offset.x * bTransform.scale.x,
		bTransform.position.y + bCollider.offset.y * bTransform.scale.y,
		bCollider.width * bTransform.scale.x,
		bCollider.height * bTransform.scale.y
	};

	if (AABBCollisionCheck(aBottomRect, bRect)) {
		spdlog::info("Ground collision detected.");
		return CollisionType::Ground;
	}
	if (AABBCollisionCheck(aTopRect, bRect)) {
		spdlog::info("Ceiling collision detected.");
		return CollisionType::Ceiling;
	}
	if (AABBCollisionCheck(aRightRect, bRect)) {
		spdlog::info("Right collision detected.");
		return CollisionType::Right;
	}
	if (AABBCollisionCheck(aLeftRect, bRect)) {
		spdlog::info("Left collision detected.");
		return CollisionType::Left;
	}

	return CollisionType::None;
}

bool CollisionSystem::AABBCollisionCheck(const Rect& a, const Rect& b) {
	return (a.x <= b.x + b.w &&
		a.x + a.w >= b.x &&
		a.y <= b.y + b.h &&
		a.y + a.h >= b.y);
}