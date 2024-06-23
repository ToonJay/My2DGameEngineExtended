#pragma once

#include <entt.hpp>

class KeyPressEvent;
class KeyReleaseEvent;
class EventBus;

struct AnimationComponent;
struct BoxColliderComponent;
struct PlayerControllerComponent;
struct RigidBodyComponent;
struct SpriteComponent;

using Animation = AnimationComponent;
using BoxCollider = BoxColliderComponent;
using PlayerController = PlayerControllerComponent;
using RigidBody = RigidBodyComponent;
using Sprite = SpriteComponent;

class PlayerControlsSystem {
public:
    static void Update(std::unique_ptr<entt::registry>& registry);
    static void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus);

private:
    static void UpdatePlayerState(PlayerController& playerController);
    static void OnKeyPress(std::unique_ptr<entt::registry>& registry, KeyPressEvent& event);
    static void OnKeyRelease(std::unique_ptr<entt::registry>& registry, KeyReleaseEvent& event);
    static void HandleMovement(const PlayerController& playerController, RigidBody& rigidBody, Animation& animation, Sprite& sprite, const BoxCollider& collider);
    static void HandleJumping(PlayerController& playerController, RigidBody& rigidBody, const BoxCollider& collider);
    static void HandleGravity(const PlayerController& playerController, RigidBody& rigidBody, const BoxCollider& collider);
};