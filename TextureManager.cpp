#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(std::string image_path, SDL_Renderer* ren) {
	SDL_Surface* tmpSurface = IMG_Load(image_path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcR, SDL_Rect dstR, SDL_Renderer* renderer, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(renderer, texture, &srcR, &dstR, 0, nullptr, flip);
}
