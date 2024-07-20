#pragma once

#include <entt.hpp>

class CollisionEvent;
class EventBus;

struct AnimationComponent;
struct BoxColliderComponent;
struct RigidBodyComponent;
struct SpriteComponent;

using Animation = AnimationComponent;
using BoxCollider = BoxColliderComponent;
using RigidBody = RigidBodyComponent;
using Sprite = SpriteComponent;

class WormEnemyAiSystem {
public:
    static void Update(std::unique_ptr<entt::registry>& registry);
    static void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus);

private:
    static void OnCollision(std::unique_ptr<entt::registry>& registry, CollisionEvent& event);
    static void HandleGravity(RigidBody& rigidBody, Animation& animation, Sprite& sprite, const BoxCollider& collider);
};