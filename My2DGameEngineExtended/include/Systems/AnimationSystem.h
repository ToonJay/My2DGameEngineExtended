#pragma once

#include "Components/AnimationComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TagComponent.h"
#include <entt.hpp>
#include <SDL.h>

class AnimationSystem {
public:
	AnimationSystem() = default;

	static void Update(std::unique_ptr<entt::registry>& registry) {
		auto view = registry->view<Animation, Sprite, Tag>();

		for (auto entity : view) {
			auto& animation = view.get<Animation>(entity);
			auto& sprite = view.get<Sprite>(entity);
			if (view.get<Tag>(entity).tag == "player") {
				if (!registry->get<BoxCollider>(entity).isGrounded) {
					sprite.assetId = "bunny-jump";
					animation.numFrames = 1;
				} else {
					sprite.assetId = "bunny-image";
					animation.numFrames = 2;
				}
			}
			animation.currentFrame = (SDL_GetTicks() - animation.startTime) * animation.currentAnimationSpeed / 1000 % animation.numFrames;
			sprite.srcRect.x = animation.currentFrame * sprite.width;
		}
	}
};