#include "AssetManager.h"
#include <spdlog.h>
#include <SDL_image.h>

AssetManager::AssetManager() {
	spdlog::info("AssetManager constructor called!");
}

AssetManager::~AssetManager() {
	spdlog::info("AssetManager destructor called!");
}

bool AssetManager::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath) {
	SDL_Surface* surface{IMG_Load(filePath.c_str())};
	if (!surface) {
		spdlog::error("Failed to load surface from file: " + filePath + " SDL_Error: " + SDL_GetError());
		return false;
	}

	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture{SDL_CreateTextureFromSurface(renderer, surface), SDL_DestroyTexture};
	SDL_FreeSurface(surface);
	if (!texture) {
		spdlog::error("Failed to create texture from surface for file: " + filePath + " SDL_Error: " + SDL_GetError());
		return false;
	}
	textures.emplace(assetId, std::move(texture));
	return true;
}

bool AssetManager::AddFont(const std::string& assetId, const std::string& filePath, const int fontSize) {
	std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font{TTF_OpenFont(filePath.c_str(), fontSize), TTF_CloseFont};
	if (!font) {
		spdlog::error("Failed to load font from file: {} with size: {} TTF_Error: {}", filePath, fontSize, TTF_GetError());
		return false;
	}
	fonts.emplace(assetId, std::move(font));
	return true;
}

SDL_Texture* AssetManager::GetTexture(const std::string& assetId) const {
	auto it = textures.find(assetId);
	if (it == textures.end()) {
		spdlog::error("Texture not found for asset ID: {}", assetId);
		return nullptr;
	}
	return it->second.get();
}

TTF_Font* AssetManager::GetFont(const std::string& assetId) const {
	auto it = fonts.find(assetId);
	if (it == fonts.end()) {
		spdlog::error("Font not found for asset ID: {}", assetId);
		return nullptr;
	}
	return it->second.get();
}