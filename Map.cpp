#include "Game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "ECS/Components.hpp"
#include "AssetManager.hpp"
#include <fstream>

extern Manager manager;

Map::Map(std::string texture, int map_scale, int tile_size, SDL_Renderer* renderer) :
	m_texture_ID(texture), m_map_scale(map_scale), m_tile_size(tile_size), m_renderer(renderer), m_scaled_size(tile_size* map_scale) {

}

Map::~Map() {
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
