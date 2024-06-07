#pragma once

#include <SDL.h>
#include <unordered_set>

struct PlayerControllerComponent {
    std::unordered_set<SDL_Keycode> activeKeys;
    int jumpTime{0};
};
using PlayerController = PlayerControllerComponent;