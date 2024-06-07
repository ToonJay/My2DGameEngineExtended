#pragma once

#include <string>
#include <SDL.h>

struct SpriteComponent {
    std::string assetId{""};
    int width{0};
    int height{0};
    SDL_Rect srcRect{0, 0, 0 ,0};
    SDL_RendererFlip flip{SDL_FLIP_NONE};
    int zIndex{0};
    bool isFixed{false};

    SpriteComponent() = default;

    SpriteComponent(const std::string& assetId, const int width, const int height, const SDL_RendererFlip& flip, const int zIndex, const bool isFixed, const int srcRectX, const int srcRectY)
        : assetId{assetId}, width {width}, height{height}, srcRect{srcRectX, srcRectY, width, height}, flip{flip}, zIndex{zIndex}, isFixed{isFixed} {}
};
using Sprite = SpriteComponent;