#include "Game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "ECS/Components.hpp"
#include "AssetManager.hpp"
#include <fstream>

extern Manager manager;

//std::vector<std::vector<int>> Map::mapFill(int rows, int cols, int code) {
//	std::vector<std::vector<int>> map;
//	std::vector<int> tmp;
//	for (int row = 0; row < rows; row++) {
//		map.push_back(tmp);
//		for (int col = 0; col < cols; col++) {
//			map[row].push_back(code);
//		}
//	}
//	return map;
//}

//Map::Map(int rows, int cols, SDL_Renderer* renderer): 
//		m_rows(rows), m_cols(cols), m_renderer(renderer)
//{
//	m_src_R.x = 0;
//	m_src_R.y = 0;
//	m_src_R.w = TextureManager::w_texture_dimension;
//	m_src_R.h = TextureManager::h_texture_dimension;
//	m_dst_R.x = 0;
//	m_dst_R.y = 0;
//	m_dst_R.h = TextureManager::h_texture_dimension;
//	m_dst_R.w = TextureManager::w_texture_dimension;
//
//
//	m_clear_space = TextureManager::LoadTexture("assets/clear_space_tile.png", m_renderer);
//	m_white_stars = TextureManager::LoadTexture("assets/white_stars_tile.png", m_renderer);
//	m_colourful_stars = TextureManager::LoadTexture("assets/colourful_stars_tile.png", m_renderer);
//	m_asteroids = TextureManager::LoadTexture("assets/asteroids_tile.png", m_renderer);
//	LoadMap();
//}

//Map::Map(std::string map_path, int map_scale, int tile_size, SDL_Renderer* renderer) :
//	m_map_file_path(map_path), m_map_scale(map_scale), m_tile_size(tile_size), m_renderer(renderer), m_scaled_size(tile_size*map_scale) {
//
//}


Map::~Map() {
	/*SDL_DestroyTexture(m_white_stars);
	SDL_DestroyTexture(m_asteroids);
	SDL_DestroyTexture(m_clear_space);
	SDL_DestroyTexture(m_colourful_stars);*/
}

//void Map::LoadMap(std::vector<std::vector<int>>* input_map)
//{
//	if (input_map == nullptr) {
//		m_map = mapFill(m_rows, m_cols, 2);
//		/*m_map[2][3] = 1;
//		m_map[5][1] = 1;
//		m_map[5][5] = 0;
//		m_map[2][4] = 3;*/
//
//	}
//	else
//	{
//		m_map = *input_map;
//	}
//}
//
//void Map::LoadMap(std::string path, int sizeX, int sizeY, SDL_Renderer* renderer) {
//	char char_tile;
//	std::fstream mapFile;
//	mapFile.open(path);
//
//	int srcX, srcY;
//
//	for (int y = 0; y < sizeY; y++) {
//		for (int x = 0; x < sizeX; x++) {
//			mapFile.get(char_tile);
//			srcY = atoi(&char_tile) * TextureManager::w_texture_dimension;
//			mapFile.get(char_tile);
//			srcX = atoi(&char_tile) * TextureManager::h_texture_dimension;
//			//Game::AddTile(atoi(&char_tile), x * TextureManager::h_texture_dimension, y * TextureManager::h_texture_dimension, renderer);
//			Game::AddTile(srcX, srcY, x * TextureManager::h_texture_dimension, y * TextureManager::h_texture_dimension, renderer);
//			mapFile.ignore();
//		}
//	}
//
//	mapFile.close();
//}
//
//void Map::DrawMap()
//{
//	for (int row = 0; row < m_rows; row++) {
//		for (int col = 0; col < m_cols; col++) {
//			m_dst_R.x = col * TextureManager::w_texture_dimension;
//			m_dst_R.y = row * TextureManager::h_texture_dimension;
//			switch (m_map[row][col]) {
//			case 0:
//				TextureManager::Draw(m_clear_space, m_src_R, m_dst_R, m_renderer);
//				break;
//			case 1:
//				TextureManager::Draw(m_white_stars, m_src_R, m_dst_R, m_renderer);
//				break;
//			case 2:
//				TextureManager::Draw(m_colourful_stars, m_src_R, m_dst_R, m_renderer);
//				break;
//			case 3:
//				TextureManager::Draw(m_asteroids, m_src_R, m_dst_R, m_renderer);
//				break;
//			}
//		}
//	}
//}






//void Map::loadMap(std::string path, int sizeX, int sizeY, SDL_Renderer* renderer) {
//	char char_tile;
//	std::fstream mapFile;
//	mapFile.open(path);
//
//	int srcX, srcY;
//
//	for (int y = 0; y < sizeY; y++) {
//		for (int x = 0; x < sizeX; x++) {
//			mapFile.get(char_tile);
//			
//			srcY = atoi(&char_tile) * m_tile_size;
//			mapFile.get(char_tile);
//			srcX = atoi(&char_tile) * m_tile_size;
//			//Game::AddTile(atoi(&char_tile), x * TextureManager::h_texture_dimension, y * TextureManager::h_texture_dimension, renderer);
//			addTile(srcX, srcY, x * m_scaled_size, y * m_scaled_size);
//			mapFile.ignore();
//		}
//	}
//
//	mapFile.ignore();
//
//	for (int y = 0; y < sizeY; y++) {
//		for (int x = 0; x < sizeX; x++) {
//			mapFile.get(char_tile);
//			if (char_tile == '1') {
//				auto& tcolid(manager.addEntity());
//				tcolid.addComponent<ColliderComponent>("terrain", x * m_scaled_size, y * m_scaled_size, m_scaled_size, m_renderer);
//				tcolid.addGroup(Game::groupColliders);
//			}
//			mapFile.ignore();
//		}
//	}
//
//	mapFile.close();
//}
//
//void Map::addTile(int srcX, int srcY, int xpos, int ypos) {
//	auto& tile(manager.addEntity());
//	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, m_tile_size, m_map_scale, m_map_file_path, m_renderer);
//	tile.addGroup(Game::groupMap);
//}

Map::Map(std::string texture, int map_scale, int tile_size, SDL_Renderer* renderer) :
	m_texture_ID(texture), m_map_scale(map_scale), m_tile_size(tile_size), m_renderer(renderer), m_scaled_size(tile_size* map_scale) {

}

void Map::loadMap(std::string path, int sizeX, int sizeY, SDL_Renderer* renderer) {
	char char_tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(char_tile);
			
			srcY = atoi(&char_tile) * m_tile_size;
			mapFile.get(char_tile);
			srcX = atoi(&char_tile) * m_tile_size;
			addTile(srcX, srcY, x * m_scaled_size, y * m_scaled_size);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(char_tile);
			if (char_tile == '1') {
				auto& tcolid(manager.addEntity());
				tcolid.addComponent<ColliderComponent>("terrain", x * m_scaled_size, y * m_scaled_size, m_scaled_size, m_renderer);
				tcolid.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::addTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, m_tile_size, m_map_scale, m_texture_ID, m_renderer);
	tile.addGroup(Game::groupMap);
}