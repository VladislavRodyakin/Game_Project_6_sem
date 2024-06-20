#pragma once
#include "Game.hpp"
#include <vector>
#include <string>

class Map {
	int m_map_scale = 0, m_tile_size = 0, m_scaled_size = 0;
	std::string m_map_file_path = "";
	std::string m_texture_ID = "";
	SDL_Renderer* m_renderer = nullptr;
	/*int m_rows, m_cols;
	SDL_Rect m_src_R, m_dst_R;

	SDL_Texture* m_white_stars;
	SDL_Texture* m_clear_space;
	SDL_Texture* m_colourful_stars;
	SDL_Texture* m_asteroids;

	std::vector<std::vector<int>> m_map;

	std::vector<std::vector<int>> mapFill(int rows, int cols, int code = 0);*/

public:
	//Map(int rows, int cols, SDL_Renderer* renderer);
	//Map(std::string map_path, int map_scale, int tile_size, SDL_Renderer* renderer);
	Map(std::string texture, int map_scale, int tile_size, SDL_Renderer* renderer);
	~Map();

	/*void LoadMap(std::vector<std::vector<int>>* input_map = nullptr);

	static void LoadMap(std::string path, int sizeX, int sizeY, SDL_Renderer* renderer);
	void DrawMap();*/
	
	void loadMap(std::string path, int sizeX, int sizeY, SDL_Renderer* renderer);
	void addTile(int srcX, int srcY, int xpos, int ypos);
};