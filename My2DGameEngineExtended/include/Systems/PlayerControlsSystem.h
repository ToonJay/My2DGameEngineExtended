#pragma once

#include "Components/PlayerControllerComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/BoxCollidercomponent.h"
#include "Components/PlayerTagComponent.h"
#include "EventBus/EventBus.h"
#include "Events/KeyPressEvent.h"
#include "Events/KeyReleaseEvent.h"
#include <entt.hpp>
#include <SDL.h>

class PlayerControlsSystem {
public:
	static void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<KeyPressEvent>(OnKeyPress);
		eventBus->SubscribeToEvent<KeyReleaseEvent>(OnKeyRelease);
	}

	static void OnKeyPress(std::unique_ptr<entt::registry>& registry, KeyPressEvent& event) {
		auto view = registry->view<Animation, PlayerController, PlayerTag, RigidBody, Sprite, BoxCollider>();
		
		for (auto entity : view) {
			auto& playerController = view.get<PlayerController>(entity);
			auto& rigidBody = view.get<RigidBody>(entity);
			auto& animation = view.get<Animation>(entity);
			auto& sprite = view.get<Sprite>(entity);
			auto& collider = view.get<BoxCollider>(entity);
			
			playerController.activeKeys.insert(event.symbol);

			bool movingRight = playerController.activeKeys.count(SDLK_RIGHT);
			bool movingLeft = playerController.activeKeys.count(SDLK_LEFT);
			bool jumping = playerController.activeKeys.count(SDLK_SPACE);

			if (movingRight && !movingLeft) {
				rigidBody.velocity.x = rigidBody.speed;
				animation.currentAnimationSpeed = animation.defaultAnimationSpeed;
				sprite.flip = SDL_FLIP_NONE;
				
			} else if (movingLeft && !movingRight) {
				rigidBody.velocity.x = -rigidBody.speed;
				animation.currentAnimationSpeed = animation.defaultAnimationSpeed;
				sprite.flip = SDL_FLIP_HORIZONTAL;
			
			} else if (movingLeft && movingRight) {
				rigidBody.velocity.x = 0;
				animation.currentAnimationSpeed = 0;
			}

			if (jumping && collider.isGrounded) {
				playerController.jumpTime = SDL_GetTicks();
				rigidBody.velocity.y = -200;
				rigidBody.gravityEnabled = false;
			}
		}
	}

	static void OnKeyRelease(std::unique_ptr<entt::registry>& registry, KeyReleaseEvent& event) {
		auto view = registry->view<Animation, PlayerController, PlayerTag, RigidBody, Sprite, BoxCollider>();

		for (auto entity : view) {
			auto& playerController = view.get<PlayerController>(entity);
			auto& rigidBody = view.get<RigidBody>(entity);
			auto& animation = view.get<Animation>(entity);
			auto& sprite = view.get<Sprite>(entity);
			auto& collider = view.get<BoxCollider>(entity);

			playerController.activeKeys.erase(event.symbol);

			bool movingRight = playerController.activeKeys.count(SDLK_RIGHT);
			bool movingLeft = playerController.activeKeys.count(SDLK_LEFT);
			bool jumping = playerController.activeKeys.count(SDLK_SPACE);

			if (movingRight && !movingLeft) {
				rigidBody.velocity.x = rigidBody.speed;
				animation.currentAnimationSpeed = animation.defaultAnimationSpeed;
				sprite.flip = SDL_FLIP_NONE;

			} else if (movingLeft && !movingRight) {
				rigidBody.velocity.x = -rigidBody.speed;
				animation.currentAnimationSpeed = animation.defaultAnimationSpeed;
				sprite.flip = SDL_FLIP_HORIZONTAL;

			} else if (movingLeft && movingRight) {
				rigidBody.velocity.x = 0;
				animation.currentAnimationSpeed = 0;
			} else if (!movingLeft && !movingRight) {
				rigidBody.velocity.x = 0;
				animation.currentAnimationSpeed = 0;
			}

			if (!jumping && !collider.isGrounded) {
				rigidBody.gravityEnabled = true;
				rigidBody.velocity.y = 0;
			}
		}
	}
};