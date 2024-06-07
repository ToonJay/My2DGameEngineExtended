#pragma once
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <memory>
#include <string>

class AssetManager {
private:
	std::unordered_map<std::string, std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> textures;
	std::unordered_map<std::string, std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>> fonts;

public:
	AssetManager();
	~AssetManager();

	bool AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);
	bool AddFont(const std::string& assetId, const std::string& filePath, const int fontSize);
	
	SDL_Texture* GetTexture(const std::string& assetId) const;
	TTF_Font* GetFont(const std::string& assetId) const;
};