#include "Game.h"
#include "Components.h"
#include "Systems.h"
#include <iostream>

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		spdlog::error("Error initializing SDL.");
		return;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	
	if (screenWidth > displayMode.w || screenHeight > displayMode.h) {
		screenWidth /= 2;
		screenHeight /= 2;

	}

	window.reset(SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_BORDERLESS));
	if (!window) {
		spdlog::error("Error creating SDL window.");
		return;
	}

	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (!renderer) {
		spdlog::error("Error creating SDL renderer.");
		return;
	}
	SDL_RenderSetLogicalSize(renderer.get(), virtualWidth, virtualHeight);

	spdlog::info("Game initialized");
}

void Game::Setup() {
	assetManager->AddTexture(renderer.get(), "bunny-image", "./assets/images/bunny.png");
	assetManager->AddTexture(renderer.get(), "bunny-jump", "./assets/images/bunny-jump.png");
	assetManager->AddTexture(renderer.get(), "tile", "./assets/tilemaps/tilemap_packed.png");

	const entt::entity entity = registry->create();
	registry->emplace<Transform>(entity, glm::vec2(200, virtualHeight/2 - 200), glm::vec2(2.0, 2.0));
	registry->emplace<RigidBody>(entity, 200, glm::vec2(0.0, 0.0), true);
	registry->emplace<Sprite>(entity, "bunny-image", 16, 16, SDL_FLIP_NONE, 0, false, 0, 0);
	registry->emplace<Animation>(entity, 2, 0, 10, true);
	registry->emplace<BoxCollider>(entity, 14, 15, glm::vec2(2, 2));
	registry->emplace<PlayerTag>(entity);
	registry->emplace<Tag>(entity, "player");
	registry->emplace<PlayerController>(entity);

	//const entt::entity tile = registry->create();
	//registry->emplace<Transform>(tile, glm::vec2(500, virtualHeight / 2), glm::vec2(2.0, 2.0));
	//registry->emplace<Sprite>(tile, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 144, 16);
	//registry->emplace<BoxCollider>(tile, 16, 16, glm::vec2(0, 0));
	//registry->emplace<Tag>(tile, "tile");

	const entt::entity tile2 = registry->create();
	registry->emplace<Transform>(tile2, glm::vec2(500, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile2, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile2, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile2, "tile");

	const entt::entity tile3 = registry->create();
	registry->emplace<Transform>(tile3, glm::vec2(468, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile3, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile3, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile3, "tile");

	const entt::entity tile4 = registry->create();
	registry->emplace<Transform>(tile4, glm::vec2(436, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile4, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile4, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile4, "tile");

	const entt::entity tile5 = registry->create();
	registry->emplace<Transform>(tile5, glm::vec2(404, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile5, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile5, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile5, "tile");

	const entt::entity tile6 = registry->create();
	registry->emplace<Transform>(tile6, glm::vec2(372, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile6, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile6, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile6, "tile");

	const entt::entity tile7 = registry->create();
	registry->emplace<Transform>(tile7, glm::vec2(340, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile7, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile7, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile7, "tile");

	const entt::entity tile8 = registry->create();
	registry->emplace<Transform>(tile8, glm::vec2(276, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile8, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile8, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile8, "tile");

	const entt::entity tile9 = registry->create();
	registry->emplace<Transform>(tile9, glm::vec2(244, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile9, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile9, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile9, "tile");

	const entt::entity tile10 = registry->create();
	registry->emplace<Transform>(tile10, glm::vec2(212, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile10, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile10, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile10, "tile");

	const entt::entity tile11 = registry->create();
	registry->emplace<Transform>(tile11, glm::vec2(180, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile11, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile11, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile11, "tile");

	const entt::entity tile12 = registry->create();
	registry->emplace<Transform>(tile12, glm::vec2(308, virtualHeight / 2 + 32), glm::vec2(2.0, 2.0));
	registry->emplace<Sprite>(tile12, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 64, 0);
	registry->emplace<BoxCollider>(tile12, 16, 16, glm::vec2(0, 0));
	registry->emplace<Tag>(tile12, "tile");

	//const entt::entity tile13 = registry->create();
	////registry->emplace<Transform>(tile13, glm::vec2(468, virtualHeight / 2 - 32), glm::vec2(2.0, 2.0));
	//registry->emplace<Sprite>(tile13, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 144, 16);
	////registry->emplace<BoxCollider>(tile13, 16, 16, glm::vec2(0, 0));
	///registry->emplace<Tag>(tile13, "tile");

	//const entt::entity tile14 = registry->create();
	//registry->emplace<Transform>(tile14, glm::vec2(500, virtualHeight / 2 - 32), glm::vec2(2.0, 2.0));
	//registry->emplace<Sprite>(tile14, "tile", 16, 16, SDL_FLIP_NONE, 0, true, 144, 16);
	//registry->emplace<BoxCollider>(tile14, 16, 16, glm::vec2(0, 0));
	//registry->emplace<Tag>(tile14, "tile");
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			if (sdlEvent.key.keysym.sym == SDLK_d) {
				isDebug = !isDebug;
			}
			eventBus->EmitEvent<KeyPressEvent>(registry, sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			eventBus->EmitEvent<KeyReleaseEvent>(registry, sdlEvent.key.keysym.sym);
			break;
		}
	}
}

void Game::Update() {
	deltaTime = (SDL_GetTicks() - previousFrameTime) / 1000.0;
	previousFrameTime = SDL_GetTicks();

	eventBus->Reset();

	PlayerControlsSystem::SubscribeToEvents(eventBus);
	MovementSystem::SubscribeToEvents(eventBus);

	AnimationSystem::Update(registry);
	MovementSystem::Update(registry, deltaTime);
	CollisionSystem::Update(registry, eventBus);
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(renderer.get());

	RenderSystem::Update(renderer.get(), registry, assetManager);

	if (isDebug) {
		RenderColliderSystem::Update(renderer.get(), registry);
	}

	SDL_RenderPresent(renderer.get());
}

void Game::Run() {
	Setup();
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Close() {
	SDL_Quit();
	spdlog::info("Game closed");
}