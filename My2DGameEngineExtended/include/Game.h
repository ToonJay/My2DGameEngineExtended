#pragma once

#include "AssetManager.h"
#include "EventBus/EventBus.h"
#include <entt.hpp>
#include <SDL.h>
#include <spdlog.h>
#include <memory>

class Game {
private:
	bool isRunning{true};
	bool isDebug{false};
	float deltaTime{0.0};
	int previousFrameTime{0};
	int screenWidth{1280};
	int screenHeight{960};
	int virtualWidth{640};
	int virtualHeight{480};

	std::unique_ptr<entt::registry> registry{std::make_unique<entt::registry>()};
	std::unique_ptr<AssetManager> assetManager{std::make_unique<AssetManager>()};
	std::unique_ptr<EventBus> eventBus{std::make_unique<EventBus>()};

	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};

public:
	Game() {
		spdlog::info("Game constructor called!");
	}
	~Game() {
		spdlog::info("Game destructor called!");
	}

	void Initialize();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Run();
	void Close();
};