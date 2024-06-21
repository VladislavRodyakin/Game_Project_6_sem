#pragma once
#include "SDL.h"
#include "Components.hpp"
#include "Animation.hpp"
#include "../AssetManager.hpp"
#include <map>

class SpriteComponent : public Component{
	SDL_Renderer* m_renderer = nullptr;
	TransformComponent* m_transform = nullptr;
	
	SDL_Texture* m_texture = nullptr;
	SDL_Rect m_srcR = { 0,0,0,0 }, m_dstR = { 0,0,0,0 };

	bool m_is_animated = false;
	int m_frames = 0;
	int m_frame_time = 100; // time between frames in ms

	int m_anim_id = 0;

	std::map<std::string, Animation> m_animations = {};

	SDL_RendererFlip m_sprite_flip = SDL_FLIP_NONE;

public:
	SpriteComponent() = default;
	SpriteComponent(std::string path, SDL_Renderer* renderer);
	SpriteComponent(std::string texture_id, bool is_animated, SDL_Renderer* renderer);
	~SpriteComponent();

	void init() override;
	void update() override;
	void draw() override;

	void setFlip(SDL_RendererFlip flip);
	void resetTexture(std::string texture_id);
	void play(std::string anim_name);
};
