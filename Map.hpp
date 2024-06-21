#pragma once
#include "Game.hpp"
#include <vector>
#include <string>

class Map {
	int m_map_scale = 0, m_tile_size = 0, m_scaled_size = 0;
	std::string m_map_file_path = "";
	std::string m_texture_ID = "";
	SDL_Renderer* m_renderer = nullptr;

public:
	Map(std::string texture, int map_scale, int tile_size, SDL_Renderer* renderer);
	~Map();
	
	void loadMap(std::string path, int sizeX, int sizeY, SDL_Renderer* renderer);
	void addTile(int srcX, int srcY, int xpos, int ypos);
};