#include "Systems/PlayerControlsSystem.h"
#include "Events/KeyPressEvent.h"
#include "Events/KeyReleaseEvent.h"
#include "EventBus/EventBus.h"
#include "Components/AnimationComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/PlayerControllerComponent.h"
#include "Components/TagComponents/PlayerTagComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/SpriteComponent.h"

void PlayerControlsSystem::Update(std::unique_ptr<entt::registry>& registry) {
    auto view = registry->view<Animation, PlayerController, PlayerTag, RigidBody, Sprite, BoxCollider>();

    for (auto entity : view) {
        auto& playerController = view.get<PlayerController>(entity);
        auto& rigidBody = view.get<RigidBody>(entity);
        auto& animation = view.get<Animation>(entity);
        auto& sprite = view.get<Sprite>(entity);
        auto& collider = view.get<BoxCollider>(entity);

        HandleMovement(playerController, rigidBody, animation, sprite, collider);
        HandleJumping(playerController, rigidBody, animation, sprite, collider);
        HandleGravity(playerController, rigidBody, animation, sprite, collider);
    }
}

void PlayerControlsSystem::SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
    eventBus->SubscribeToEvent<KeyPressEvent>(OnKeyPress);
    eventBus->SubscribeToEvent<KeyReleaseEvent>(OnKeyRelease);
}

void PlayerControlsSystem::UpdatePlayerState(PlayerController& playerController) {
    playerController.isMovingRight = playerController.activeKeys.count(SDLK_RIGHT);
    playerController.isMovingLeft = playerController.activeKeys.count(SDLK_LEFT);
    playerController.isJumping = playerController.activeKeys.count(SDLK_SPACE);
}

void PlayerControlsSystem::OnKeyPress(std::unique_ptr<entt::registry>& registry, KeyPressEvent& event) {
    auto view = registry->view<PlayerController, PlayerTag>();

    for (auto entity : view) {
        auto& playerController = view.get<PlayerController>(entity);

        if (playerController.activeKeys.count(event.symbol) == 0) {
            playerController.activeKeys.insert(event.symbol);
            UpdatePlayerState(playerController);
        }
    }
}

void PlayerControlsSystem::OnKeyRelease(std::unique_ptr<entt::registry>& registry, KeyReleaseEvent& event) {
    auto view = registry->view<PlayerController, PlayerTag>();

    for (auto entity : view) {
        auto& playerController = view.get<PlayerController>(entity);

        playerController.activeKeys.erase(event.symbol);
        UpdatePlayerState(playerController);
    }
}

void PlayerControlsSystem::HandleMovement(const PlayerController& playerController, RigidBody& rigidBody, Animation& animation, Sprite& sprite, const BoxCollider& collider) {
    if (playerController.isMovingRight) {
        sprite.flip = SDL_FLIP_NONE;
    } else if (playerController.isMovingLeft) {
        sprite.flip = SDL_FLIP_HORIZONTAL;
    }

    if (playerController.isMovingRight && !playerController.isMovingLeft && !collider.isTouchingRightWall) {
        rigidBody.velocity.x = rigidBody.speed;
        animation.currentAnimationSpeed = animation.defaultAnimationSpeed;
        
    } else if (playerController.isMovingLeft && !playerController.isMovingRight && !collider.isTouchingLeftWall) {
        rigidBody.velocity.x = -rigidBody.speed;
        animation.currentAnimationSpeed = animation.defaultAnimationSpeed;
        
    } else {
        rigidBody.velocity.x = 0;
        animation.currentAnimationSpeed = 0;
    }
}

void PlayerControlsSystem::HandleJumping(PlayerController& playerController, RigidBody& rigidBody, Animation& animation, Sprite& sprite, const BoxCollider& collider) {
    if (playerController.isJumping && collider.isGrounded && !collider.isTouchingCeiling) {
        playerController.jumpTime = SDL_GetTicks();
        sprite.assetId = "bunny-jump";
        animation.numFrames = 1;
    }

    if (playerController.isJumping && (SDL_GetTicks() - playerController.jumpTime) <= playerController.jumpTimeLimit && !collider.isTouchingCeiling) {
        rigidBody.velocity.y = -rigidBody.jumpSpeed; 
    } else {
        playerController.jumpTime = 0;
        playerController.isJumping = false; 
    }
}

void PlayerControlsSystem::HandleGravity(const PlayerController& playerController, RigidBody& rigidBody, Animation& animation, Sprite& sprite, const BoxCollider& collider) {
    if (collider.isGrounded && !playerController.isJumping) {
        rigidBody.velocity.y = 0;
        sprite.assetId = "bunny-image";
        animation.numFrames = 2;
    }

    if (!playerController.isJumping && !collider.isGrounded) {
        rigidBody.velocity.y = rigidBody.fallSpeed;
        sprite.assetId = "bunny-jump";
        animation.numFrames = 1;
    }
}