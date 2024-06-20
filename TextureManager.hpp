#pragma once
#include "Game.hpp"


class TextureManager {
public:
	static const int w_texture_dimension = 50;
	static const int h_texture_dimension = 50;

	static SDL_Texture* LoadTexture(std::string image_path, SDL_Renderer* ren);
	static void Draw(SDL_Texture* texture, SDL_Rect srcR, SDL_Rect dstR, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
};