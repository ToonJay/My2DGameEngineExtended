#pragma once

#include <entt.hpp>

class CollisionEvent;
enum class CollisionType;
class EventBus;

class MovementSystem {
public:
    static void Update(std::unique_ptr<entt::registry>& registry, const float deltaTime);
    static void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus);

private:
    static void OnCollision(std::unique_ptr<entt::registry>& registry, CollisionEvent& event);
    static void PlayerEnvironmentCollision(std::unique_ptr<entt::registry>& registry, entt::entity a, entt::entity b, CollisionType collisionType);
    static void EnemyEnvironmentCollision(std::unique_ptr<entt::registry>& registry, entt::entity a, entt::entity b, CollisionType collisionType);
    static void EnemyEnemyCollision(std::unique_ptr<entt::registry>& registry, entt::entity a, entt::entity b, CollisionType collisionType);
};