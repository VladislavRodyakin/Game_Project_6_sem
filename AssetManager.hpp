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
	//weak requires lock() wich causes problems with uniq_ptrs inside Manager
	//shared_ptrs cause errors on game close


public:
	//AssetManager() = default;
	AssetManager(Manager* manager);
	~AssetManager();


	//game object management
	void CreateProjectile(Vector2D pos, Vector2D direction, int range, int speed, const std::string& texture_id, SDL_Renderer* renderer);
	void CreateProjectileRandom(int min_speed, int max_speed, const std::string& texture_id, SDL_Renderer* renderer);


	//texture management
	void AddTexture(const std::string& id, const std::string& path, SDL_Renderer* renderer);
	SDL_Texture* GetTexture(const std::string& id);
	
	
	//texture management
	void AddFont(const std::string& id, const std::string& path, int size);
	TTF_Font* GetFont(const std::string& id);



};