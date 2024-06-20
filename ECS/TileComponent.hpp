#pragma once
#include "SDL.h"
#include "ECS.hpp"
#include "Components.hpp"
#include "../AssetManager.hpp"
#include <string>

//class TileComponent : public Component {
//	TransformComponent* m_transform;
//	SpriteComponent* m_sprite;
//	SDL_Renderer* m_renderer;
//	SDL_Rect m_tileR;
//	std::string path;
//	int m_tileID;
//public:
//	TileComponent() = default;
//	TileComponent(int x, int y, int h, int w, int id, SDL_Renderer* renderer): m_tileID(id), m_renderer(renderer) {
//		m_tileR.x = x;
//		m_tileR.y = y;
//		m_tileR.h = h;
//		m_tileR.w = w;
//
//		//see Map for refactor
//		switch (m_tileID)
//		{
//		case 0:
//			path = "assets/clear_space_tile.png";
//			break;
//		case 1:
//			path = "assets/white_stars_tile.png";
//			break;
//		case 2:
//			path = "assets/colourful_stars_tile.png";
//			break;
//		case 3:
//			path = "assets/asteroids_tile.png";
//			break;
//		default:
//			break;
//		}
//	}
//
//	void init() override {
//		m_entity->addComponent<TransformComponent>(m_tileR.x, m_tileR.y, m_tileR.h, m_tileR.w, 1);
//		m_transform = &m_entity->getComponent<TransformComponent>();
//
//		m_entity->addComponent<SpriteComponent>(path, m_renderer);
//		m_sprite = &m_entity->getComponent<SpriteComponent>();
//	}
//
//	void update() override {
//		return;
//	}
//};

class TileComponent : public Component {
	SDL_Texture* m_texture = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Rect m_src_r = { 0,0,0,0 }, m_dst_r = { 0,0,0,0 };
	Vector2D m_position = { 0,0 };
public:
	/*TileComponent(int srcX, int srcY, int xpos, int ypos, const std::string& path, SDL_Renderer* renderer) : m_renderer(renderer) {
		m_texture = TextureManager::LoadTexture(path, renderer);
		
		m_position.x(xpos);
		m_position.y(ypos);
		
		m_src_r.x = srcX;
		m_src_r.y = srcY;
		m_src_r.h = TextureManager::h_texture_dimension;
		m_src_r.w = TextureManager::w_texture_dimension;

		m_dst_r.x = xpos;
		m_dst_r.y = ypos;
		m_dst_r.h = TextureManager::h_texture_dimension;
		m_dst_r.w = TextureManager::w_texture_dimension;
	}*/

	/*TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const std::string& path, SDL_Renderer* renderer) : m_renderer(renderer) {
		m_texture = TextureManager::LoadTexture(path, renderer);

		m_position.x(xpos);
		m_position.y(ypos);

		m_src_r.x = srcX;
		m_src_r.y = srcY;
		m_src_r.h = tsize;
		m_src_r.w = tsize;

		m_dst_r.x = xpos;
		m_dst_r.y = ypos;
		m_dst_r.h = tsize * tscale;
		m_dst_r.w = tsize * tscale;
	}*/
	
	TileComponent() = default;
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const std::string& texture_id, SDL_Renderer* renderer);
	~TileComponent();

	int getDestX();
	void setDestX(int x);
	void addDestX(int x);
	int getDestY();
	void setDestY(int y);
	void addDestY(int y);

	void draw() override;
	void update() override;
};
