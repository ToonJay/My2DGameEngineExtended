#include "Systems/MovementSystem.h"
#include "Events/CollisionEvent.h"
#include "EventBus/EventBus.h"
#include "Components/RigidBodyComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PlayerTagComponent.h"
#include "Components/TagComponent.h"
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
    entt::entity a;
    entt::entity b;

    if (registry->get<Tag>(event.a).tag != "player" && registry->get<Tag>(event.b).tag == "player") {
        a = event.b;
        b = event.a;
    } else if (registry->get<Tag>(event.a).tag == "player" && registry->get<Tag>(event.b).tag != "player") {
        a = event.a;
        b = event.b;
    } else {
        return;
    }

    auto& aTransform = registry->get<Transform>(a);
    auto& aCollider = registry->get<BoxCollider>(a);
    auto& aRigidBody = registry->get<RigidBody>(a);

    auto& bTransform = registry->get<Transform>(b);
    auto& bCollider = registry->get<BoxCollider>(b);

    if (event.collisionType == CollisionType::Ground) {
        aTransform.position.y -= aTransform.position.y + (aCollider.height + aCollider.offset.y + 2) * aTransform.scale.y - bTransform.position.y;
    } else if (event.collisionType == CollisionType::Right) {
        aTransform.position.x -= aTransform.position.x + (aCollider.width + aCollider.offset.x + 2) * aTransform.scale.x - bTransform.position.x;
    } else if (event.collisionType == CollisionType::Ceiling) {
        aTransform.position.y += bTransform.position.y + (bCollider.height + bCollider.offset.y) * bTransform.scale.y - aTransform.position.y - 2 * aTransform.scale.y / 2;
    } else if (event.collisionType == CollisionType::Left) {
        aTransform.position.x += bTransform.position.x + (bCollider.width + bCollider.offset.x) * bTransform.scale.x - aTransform.position.x - 2 * aTransform.scale.x;
    }
}