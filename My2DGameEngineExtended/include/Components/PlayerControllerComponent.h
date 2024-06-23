#pragma once

#include <SDL.h>
#include <unordered_set>

struct PlayerControllerComponent {
    std::unordered_set<SDL_Keycode> activeKeys;
    Uint32 jumpTime{0};
    Uint32 jumpTimeLimit{0};
    bool isMovingRight{false};
    bool isMovingLeft{false};
    bool isJumping{false};

    PlayerControllerComponent(const Uint32 jumpTimeLimit) : jumpTimeLimit{jumpTimeLimit} {}
};
using PlayerController = PlayerControllerComponent;