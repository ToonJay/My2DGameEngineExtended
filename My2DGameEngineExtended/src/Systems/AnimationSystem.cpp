#include "Systems/AnimationSystem.h"
#include "Components/AnimationComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/SpriteComponent.h"

void AnimationSystem::Update(std::unique_ptr<entt::registry>& registry) {
	auto view = registry->view<Animation, Sprite>();

	for (auto entity : view) {
		auto& animation = view.get<Animation>(entity);
		auto& sprite = view.get<Sprite>(entity);
		animation.currentFrame = (SDL_GetTicks() - animation.startTime) * animation.currentAnimationSpeed / 1000 % animation.numFrames;
		sprite.srcRect.x = animation.currentFrame * sprite.width;
	}
}