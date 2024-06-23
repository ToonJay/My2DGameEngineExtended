#pragma once

#include <entt.hpp>

class CollisionEvent;
class EventBus;

class MovementSystem {
public:
    static void Update(std::unique_ptr<entt::registry>& registry, const float deltaTime);
    static void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus);

private:
    static void OnCollision(std::unique_ptr<entt::registry>& registry, CollisionEvent& event);
};