#pragma once
#include "Game.hpp"


namespace TextureManager {
	const SDL_Color WHITE = { 255, 255, 255, 255 };
	const SDL_Color BLACK = { 0, 0, 0, 255 };

	const int w_texture_dimension = 50;
	const int h_texture_dimension = 50;

	SDL_Texture* LoadTexture(std::string image_path, SDL_Renderer* ren);
	void Draw(SDL_Texture* texture, SDL_Rect srcR, SDL_Rect dstR, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
};