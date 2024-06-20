#pragma once

#include <unordered_map>
#include <string>
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "ECS/ECS.hpp"
#include "SDL_ttf.h"

class AssetManager {
	std::unordered_map<std::string, SDL_Texture*> m_textures = {};
	std::unordered_map<std::string, TTF_Font*> m_fonts = {};
	Manager* m_manager = nullptr;


public:
	//AssetManager() = default;
	AssetManager(Manager* manager);
	~AssetManager();


	//game object management
	void CreateProjectile(Vector2D pos, Vector2D direction, int range, int speed, std::string texture_id, SDL_Renderer* renderer);


	//texture management
	void AddTexture(std::string id, std::string path, SDL_Renderer* renderer);
	SDL_Texture* GetTexture(std::string id);
	
	
	//texture management
	void AddFont(std::string id, std::string path, int size);
	TTF_Font* GetFont(std::string id);



};