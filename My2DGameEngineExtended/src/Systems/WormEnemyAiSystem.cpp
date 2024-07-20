#include "Systems/WormEnemyAiSystem.h"
#include "Events/CollisionEvent.h"
#include "EventBus/EventBus.h"
#include "Components/AnimationComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TagComponents/EnemyTagComponent.h"
#include "Components/TagComponents/WormTagComponent.h"
#include "Components/TagComponents/PlayerTagComponent.h"
#include "Components/TagComponents/TileTagComponent.h"

void WormEnemyAiSystem::Update(std::unique_ptr<entt::registry>& registry) {
	auto view = registry->view<Animation, RigidBody, Sprite, BoxCollider, EnemyTag, WormTag>();

	for (auto entity : view) {
		auto& rigidBody = view.get<RigidBody>(entity);
		auto& animation = view.get<Animation>(entity);
		auto& sprite = view.get<Sprite>(entity);
		auto& collider = view.get<BoxCollider>(entity);

		HandleGravity(rigidBody, animation, sprite, collider);
	}
}
void WormEnemyAiSystem::SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
	eventBus->SubscribeToEvent<CollisionEvent>(OnCollision);
}

void WormEnemyAiSystem::OnCollision(std::unique_ptr<entt::registry>& registry, CollisionEvent& event) {
	if (registry->all_of<EnemyTag, WormTag>(event.a)) {
		auto& aRigidBody = registry->get<RigidBody>(event.a);
		auto& aSprite = registry->get<Sprite>(event.a);

		if (event.collisionType == CollisionType::Left && aSprite.flip == SDL_FLIP_HORIZONTAL) {
			aSprite.flip = SDL_FLIP_NONE;
			aRigidBody.velocity.x = aRigidBody.speed;

			if (registry->all_of<EnemyTag, WormTag>(event.b)) {
				auto& bRigidBody = registry->get<RigidBody>(event.b);
				auto& bSprite = registry->get<Sprite>(event.b);
				if (bSprite.flip == SDL_FLIP_NONE) {
					bSprite.flip = SDL_FLIP_HORIZONTAL;
					bRigidBody.velocity.x = -bRigidBody.speed;
				}
			}
		} else if (event.collisionType == CollisionType::Right && aSprite.flip == SDL_FLIP_NONE) {
			aSprite.flip = SDL_FLIP_HORIZONTAL;
			aRigidBody.velocity.x = -aRigidBody.speed;

			if (registry->all_of<EnemyTag, WormTag>(event.b)) {
				auto& bRigidBody = registry->get<RigidBody>(event.b);
				auto& bSprite = registry->get<Sprite>(event.b);
				if (bSprite.flip == SDL_FLIP_HORIZONTAL) {
					bSprite.flip = SDL_FLIP_NONE;
					bRigidBody.velocity.x = bRigidBody.speed;
				} 
			}
		}
	}
}

void WormEnemyAiSystem::HandleGravity(RigidBody& rigidBody, Animation& animation, Sprite& sprite, const BoxCollider& collider) {
	if (collider.isGrounded) {
		rigidBody.velocity.y = 0;
		animation.currentAnimationSpeed = animation.defaultAnimationSpeed;
	} else {
		rigidBody.velocity.y = rigidBody.fallSpeed;
		animation.currentAnimationSpeed = 0;
	}
}