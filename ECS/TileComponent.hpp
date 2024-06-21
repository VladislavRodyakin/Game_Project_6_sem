#pragma once
#include "SDL.h"
#include "ECS.hpp"
#include "Components.hpp"
#include "../AssetManager.hpp"
#include <string>

class TileComponent : public Component {
	SDL_Texture* m_texture = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Rect m_src_r = { 0,0,0,0 }, m_dst_r = { 0,0,0,0 };
	Vector2D m_position = { 0,0 };
public:
	
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
