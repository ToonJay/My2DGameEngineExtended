#include "Systems/MovementSystem.h"
#include "Events/CollisionEvent.h"
#include "EventBus/EventBus.h"
#include "Components/RigidBodyComponent.h"
#include "Components/TransformComponent.h"
#include "Components/TagComponents/PlayerTagComponent.h"
#include "Components/TagComponents/EnemyTagComponent.h"
#include "Components/TagComponents/TileTagComponent.h"
#include "Components/BoxColliderComponent.h"
#include <spdlog.h>

void MovementSystem::Update(std::unique_ptr<entt::registry>& registry, const float deltaTime) {
    auto view = registry->view<RigidBody, Transform>();

    for (auto entity : view) {
        auto& rigidBody = view.get<RigidBody>(entity);
        auto& transform = view.get<Transform>(entity);

        if (rigidBody.velocity.x == 0) {
            rigidBody.accumulatedMovement.x = 0;
        }
        if (rigidBody.velocity.y == 0) {
            rigidBody.accumulatedMovement.y = 0;
        }

        rigidBody.accumulatedMovement.x += rigidBody.velocity.x * deltaTime;
        rigidBody.accumulatedMovement.y += rigidBody.velocity.y * deltaTime;

        if (std::abs(rigidBody.accumulatedMovement.x) >= 1.0) {
            int movementInt = static_cast<int>(rigidBody.accumulatedMovement.x);
            transform.position.x += movementInt;
            rigidBody.accumulatedMovement.x -= movementInt;
        }
        if (std::abs(rigidBody.accumulatedMovement.y) >= 1.0) {
            int movementInt = static_cast<int>(rigidBody.accumulatedMovement.y);
            transform.position.y += movementInt;
            rigidBody.accumulatedMovement.y -= movementInt;
        }
    }
}

void MovementSystem::SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
    eventBus->SubscribeToEvent<CollisionEvent>(OnCollision);
}

void MovementSystem::OnCollision(std::unique_ptr<entt::registry>& registry, CollisionEvent& event) {
    if (registry->any_of<PlayerTag>(event.a) && registry->any_of<TileTag>(event.b)) {
        PlayerEnvironmentCollision(registry, event.a, event.b, event.collisionType);
    } else if (registry->any_of<TileTag>(event.a) && registry->any_of<PlayerTag>(event.b)) {
        PlayerEnvironmentCollision(registry, event.b, event.a, event.collisionType);
    } else if (registry->any_of<EnemyTag>(event.a) && registry->any_of<TileTag>(event.b)) {
        EnemyEnvironmentCollision(registry, event.a, event.b, event.collisionType);
    } else if (registry->any_of<TileTag>(event.a) && registry->any_of<EnemyTag>(event.b)) {
        EnemyEnvironmentCollision(registry, event.b, event.a, event.collisionType);
    } else if (registry->any_of<EnemyTag>(event.a) && registry->any_of<EnemyTag>(event.b)) {
        EnemyEnemyCollision(registry, event.a, event.b, event.collisionType);
    }
}

void MovementSystem::PlayerEnvironmentCollision(std::unique_ptr<entt::registry>& registry, entt::entity a, entt::entity b, CollisionType collisionType) {
    auto& aTransform = registry->get<Transform>(a);
    auto& aCollider = registry->get<BoxCollider>(a);

    auto& bTransform = registry->get<Transform>(b);
    auto& bCollider = registry->get<BoxCollider>(b);

    if (collisionType == CollisionType::Ground) {
        aTransform.position.y -= aTransform.position.y + (aCollider.height + aCollider.offset.y + aCollider.margin + bCollider.margin) * aTransform.scale.y - bTransform.position.y;
    } else if (collisionType == CollisionType::Right) {
        aTransform.position.x -= aTransform.position.x + (aCollider.width + aCollider.offset.x + aCollider.margin + bCollider.margin) * aTransform.scale.x - bTransform.position.x;
    } else if (collisionType == CollisionType::Ceiling) {
        aTransform.position.y += bTransform.position.y + (bCollider.height + bCollider.offset.y) * bTransform.scale.y - aTransform.position.y - (aCollider.margin + bCollider.margin) * aTransform.scale.y / 2;
    } else if (collisionType == CollisionType::Left) {
        aTransform.position.x += bTransform.position.x + (bCollider.width + bCollider.offset.x) * bTransform.scale.x - aTransform.position.x - (aCollider.margin + bCollider.margin) * aTransform.scale.x;
    }
}

void MovementSystem::EnemyEnvironmentCollision(std::unique_ptr<entt::registry>& registry, entt::entity a, entt::entity b, CollisionType collisionType) {
    auto& aTransform = registry->get<Transform>(a);
    auto& aCollider = registry->get<BoxCollider>(a);

    auto& bTransform = registry->get<Transform>(b);
    auto& bCollider = registry->get<BoxCollider>(b);

    if (collisionType == CollisionType::Ground) {
        aTransform.position.y -= aTransform.position.y + (aCollider.height + aCollider.offset.y + aCollider.margin + bCollider.margin) * aTransform.scale.y - bTransform.position.y;
    } else if (collisionType == CollisionType::Right) {
        aTransform.position.x -= aTransform.position.x + (aCollider.width + aCollider.offset.x + aCollider.margin + bCollider.margin) * aTransform.scale.x - bTransform.position.x;
    } else if (collisionType == CollisionType::Ceiling) {
        aTransform.position.y += bTransform.position.y + (bCollider.height + bCollider.offset.y) * bTransform.scale.y - aTransform.position.y - (aCollider.margin + bCollider.margin) * aTransform.scale.y / 2;
    } else if (collisionType == CollisionType::Left) {
        aTransform.position.x += bTransform.position.x + (bCollider.width + bCollider.offset.x) * bTransform.scale.x - aTransform.position.x - (aCollider.margin + bCollider.margin) * aTransform.scale.x;
    }
}

void MovementSystem::EnemyEnemyCollision(std::unique_ptr<entt::registry>& registry, entt::entity a, entt::entity b, CollisionType collisionType) {
    auto& aTransform = registry->get<Transform>(a);
    auto& aCollider = registry->get<BoxCollider>(a);

    auto& bTransform = registry->get<Transform>(b);
    auto& bCollider = registry->get<BoxCollider>(b);

    if (collisionType == CollisionType::Ground) {
        aTransform.position.y -= (aTransform.position.y + (aCollider.height + aCollider.margin + bCollider.margin) * aTransform.scale.y - bTransform.position.y) / 2;
        bTransform.position.y += (aTransform.position.y + (aCollider.height + aCollider.margin + bCollider.margin) * aTransform.scale.y - bTransform.position.y) / 2;
    } else if (collisionType == CollisionType::Right) {
        aTransform.position.x -= (aTransform.position.x + (aCollider.width + aCollider.margin + bCollider.margin) * aTransform.scale.x - bTransform.position.x) / 2;
        bTransform.position.x += (aTransform.position.x + (aCollider.width + aCollider.margin + bCollider.margin) * aTransform.scale.x - bTransform.position.x) / 2;
    } else if (collisionType == CollisionType::Ceiling) {
        aTransform.position.y += (bTransform.position.y + (bCollider.height + bCollider.margin + aCollider.margin) * bTransform.scale.y - aTransform.position.y) / 2;
        bTransform.position.y -= (bTransform.position.y + (bCollider.height + bCollider.margin + aCollider.margin) * bTransform.scale.y - aTransform.position.y) / 2;
    } else if (collisionType == CollisionType::Left) {
        aTransform.position.x += (bTransform.position.x + (bCollider.width + bCollider.margin + aCollider.margin) * bTransform.scale.x - aTransform.position.x) / 2;
        bTransform.position.x -= (bTransform.position.x + (bCollider.width + bCollider.margin + aCollider.margin) * bTransform.scale.x - aTransform.position.x) / 2;
    }
}