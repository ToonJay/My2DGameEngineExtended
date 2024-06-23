#pragma once

#include <entt.hpp>

struct SDL_Renderer;

class RenderColliderSystem {
public:
	static void Update(SDL_Renderer* renderer, std::unique_ptr<entt::registry>& registry);
};