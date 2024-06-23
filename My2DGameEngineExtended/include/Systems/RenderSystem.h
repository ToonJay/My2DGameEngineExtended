#pragma once

#include <entt.hpp>

class AssetManager;

struct SDL_Renderer;

class RenderSystem {
public:
	static void Update(SDL_Renderer* renderer, std::unique_ptr<entt::registry>& registry, std::unique_ptr<AssetManager>& assetManager);
};