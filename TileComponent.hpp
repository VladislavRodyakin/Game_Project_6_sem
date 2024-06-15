#pragma once
#include "SDL.h"
#include "ECS.hpp"
#include "Components.hpp"

class TileComponent : public Component {
	TransformComponent* m_transform;
	SpriteComponent* m_sprite;
	SDL_Renderer* m_renderer;
	SDL_Rect m_tileR;
	std::string path;
	int m_tileID;
public:
	TileComponent() = default;
	TileComponent(int x, int y, int h, int w, int id, SDL_Renderer* renderer): m_tileID(id), m_renderer(renderer) {
		m_tileR.x = x;
		m_tileR.y = y;
		m_tileR.h = h;
		m_tileR.w = w;

		//see Map for refactor
		switch (m_tileID)
		{
		case 0:
			path = "assets/clear_space_tile.png";
			break;
		case 1:
			path = "assets/white_stars_tile.png";
			break;
		case 2:
			path = "assets/colourful_stars_tile.png";
			break;
		case 3:
			path = "assets/asteroids_tile.png";
			break;
		default:
			break;
		}
	}

	void init() override {
		m_entity->addComponent<TransformComponent>(m_tileR.x, m_tileR.y, m_tileR.h, m_tileR.w, 1);
		m_transform = &m_entity->getComponent<TransformComponent>();

		m_entity->addComponent<SpriteComponent>(path, m_renderer);
		m_sprite = &m_entity->getComponent<SpriteComponent>();
	}

	void update() override {
		return;
	}
};
