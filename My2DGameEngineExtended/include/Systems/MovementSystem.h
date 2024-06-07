#pragma once

#include "Components/RigidBodyComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PlayerTagComponent.h"
#include "Components/TagComponent.h"
#include <entt.hpp>
#include <spdlog.h>

class MovementSystem {
public:
	static void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<CollisionEvent>(OnCollision);
	}

	static void OnCollision(std::unique_ptr<entt::registry>& registry, CollisionEvent& event) {
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
            
        // Check for collision between scaled colliders
        if (aTransform.position.y + (aCollider.height * aTransform.scale.y) > bTransform.position.y &&
            aTransform.position.y < bTransform.position.y + (bCollider.height * bTransform.scale.y)) {

            // Determine the direction of collision on y-axis
            float overlapTop = (aTransform.position.y + 3 + (aCollider.height * aTransform.scale.y)) - bTransform.position.y;
            float overlapBottom = (bTransform.position.y + 3 + (bCollider.height * bTransform.scale.y)) - aTransform.position.y;

            // Adjust player's position based on the smaller overlap (y-axis)
            if (overlapTop < overlapBottom && aRigidBody.velocity.y > 0) {
                aTransform.position.y -= overlapTop;
                aRigidBody.velocity.y = 0;
            }
           // if (overlapTop > overlapBottom && aRigidBody.velocity.y < 0) {
           //     aTransform.position.y += overlapBottom;
           //     aRigidBody.velocity.y = 0;
           // }

            // Check for collision between scaled colliders on x-axis
          //  float overlapLeft = (aTransform.position.x + (aCollider.width * aTransform.scale.x)) - bTransform.position.x;
          //  float overlapRight = (bTransform.position.x + (bCollider.width * bTransform.scale.x)) - aTransform.position.x;

            // Adjust player's position based on the smaller overlap (x-axis)
           // if (overlapLeft < overlapRight && aRigidBody.velocity.x > 0) {
           //     aTransform.position.x -= overlapLeft;
           //     aRigidBody.velocity.x = 0;
           // }
           // if (overlapLeft> overlapRight && aRigidBody.velocity.x < 0) {
            //    aTransform.position.x += overlapRight;
            //    aRigidBody.velocity.x = 0;
            //}
        }
	}

	static void Update(std::unique_ptr<entt::registry>& registry, const float deltaTime) {
		auto view = registry->view<RigidBody, Transform>();

		for (auto entity : view) {
			auto& rigidBody = view.get<RigidBody>(entity);
			auto& transform = view.get<Transform>(entity);

            if (registry->get<Tag>(entity).tag == "player") {
                if ((rigidBody.gravityEnabled && !registry->get<BoxCollider>(entity).isGrounded && !registry->get<PlayerController>(entity).activeKeys.count(SDLK_SPACE))
                    || (registry->get<PlayerController>(entity).jumpTime > 0 && SDL_GetTicks() - registry->get<PlayerController>(entity).jumpTime > 500) &&
                    registry->get<PlayerController>(entity).activeKeys.count(SDLK_SPACE)) {
                    rigidBody.velocity.y = 200;
                } else if (registry->get<BoxCollider>(entity).isGrounded && !registry->get<PlayerController>(entity).activeKeys.count(SDLK_SPACE)) {
                    rigidBody.velocity.y = 0;
                }
            } 

			transform.position.x += rigidBody.velocity.x * deltaTime;
			transform.position.y += rigidBody.velocity.y * deltaTime;
		}
	}
};