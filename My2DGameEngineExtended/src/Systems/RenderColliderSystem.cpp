#include "Systems/RenderColliderSystem.h"
#include "Components/BoxColliderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PlayerTagComponent.h"
#include <SDL.h>

void RenderColliderSystem::Update(SDL_Renderer* renderer, std::unique_ptr<entt::registry>& registry) {
	auto view = registry->view<BoxCollider, Transform, PlayerTag>();

	for (auto entity : view) {
		const auto transform = view.get<Transform>(entity);
		const auto collider = view.get<BoxCollider>(entity);

		SDL_Rect colliderRect = {
			static_cast<int>(transform.position.x + collider.offset.x * transform.scale.x),
			static_cast<int>(transform.position.y + collider.offset.y * transform.scale.y),
			static_cast<int>(collider.width * transform.scale.x),
			static_cast<int>(collider.height * transform.scale.y)
		};
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &colliderRect);

		SDL_Rect colliderRect2 = {
			static_cast<int>(transform.position.x + collider.offset.x * transform.scale.x),
			static_cast<int>(transform.position.y + (collider.height + collider.offset.y) * transform.scale.y),
			static_cast<int>(collider.width * transform.scale.x),
			static_cast<int>(2 * transform.scale.y)
		};
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &colliderRect2);

		SDL_Rect colliderRect3 = {
			static_cast<int>(transform.position.x + collider.offset.x * transform.scale.x),
			static_cast<int>(transform.position.y + (collider.offset.y - 2) * transform.scale.y),
			static_cast<int>(collider.width * transform.scale.x),
			static_cast<int>(2 * transform.scale.y)
		};
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &colliderRect3);

		SDL_Rect colliderRect4 = {
			static_cast<int>(transform.position.x + (collider.width + collider.offset.x) * transform.scale.x),
			static_cast<int>(transform.position.y + collider.offset.y * transform.scale.y),
			static_cast<int>(2 * transform.scale.x),
			static_cast<int>(collider.height * transform.scale.y)
		};
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &colliderRect4);

		SDL_Rect colliderRect5 = {
			static_cast<int>(transform.position.x + (collider.offset.x - 2) * transform.scale.x),
			static_cast<int>(transform.position.y + collider.offset.y * transform.scale.y),
			static_cast<int>(2 * transform.scale.x),
			static_cast<int>(collider.height * transform.scale.y)
		};
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &colliderRect5);
	}
}