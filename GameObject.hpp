#pragma once
#include "SDL.h"
#include <string>
class GameObject
{
	int m_xpos = 0, m_ypos = 0;
	SDL_Texture* m_obj_texture;
	SDL_Rect m_src_R, m_dst_R;
	SDL_Renderer* m_renderer;

public:
	GameObject(std::string texture_path, SDL_Renderer* renderer, int xpos = 0, int ypos = 0);
	~GameObject();
	void update();
	void render();
};

