#pragma once

#include <entt.hpp>

class EventBus;
struct TransformComponent;
struct BoxColliderComponent;
enum class CollisionType;
struct Rect;

using Transform = TransformComponent;
using BoxCollider = BoxColliderComponent;

class CollisionSystem {
public:
    static void Update(std::unique_ptr<entt::registry>& registry, std::unique_ptr<EventBus>& eventBus);

private:
    static CollisionType CheckCollision(const Transform& aTransform, const BoxCollider& aCollider, const Transform& bTransform, const BoxCollider& bCollider);
    static bool AABBCollisionCheck(const Rect& a, const Rect& b);
};