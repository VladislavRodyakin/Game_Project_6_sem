#pragma once
#include "Game.hpp"
#include <vector>

class Map {
	int m_rows, m_cols;
	SDL_Rect m_src_R, m_dst_R;
	SDL_Renderer* m_renderer;

	SDL_Texture* m_white_stars;
	SDL_Texture* m_clear_space;
	SDL_Texture* m_colourful_stars;
	SDL_Texture* m_asteroids;

	std::vector<std::vector<int>> m_map;

	std::vector<std::vector<int>> mapFill(int rows, int cols, int code = 0);

public:
	Map(int rows, int cols, SDL_Renderer* renderer);
	~Map();

	void LoadMap(std::vector<std::vector<int>>* input_map = nullptr);
	void DrawMap();
	
};