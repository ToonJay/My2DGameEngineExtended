#pragma once

#include "Components/BoxColliderComponent.h"
#include "Components/TransformComponent.h"
#include <entt.hpp>
#include <SDL.h>

class RenderColliderSystem {
public:
	static void Update(SDL_Renderer* renderer, std::unique_ptr<entt::registry>& registry) {
		auto view = registry->view<BoxCollider, Transform>();

		for (auto entity : view) {
			const auto transform = view.get<Transform>(entity);
			const auto collider = view.get<BoxCollider>(entity);

			SDL_Rect colliderRect = {
				static_cast<int>(transform.position.x + collider.offset.x),
				static_cast<int>(transform.position.y + collider.offset.y),
				static_cast<int>(collider.width * transform.scale.x),
				static_cast<int>(collider.height * transform.scale.y)
			};
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &colliderRect);
		}
	}
};