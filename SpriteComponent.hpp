#pragma once
#include "SDL.h"
#include "Components.hpp"

class SpriteComponent : public Component{
	SDL_Renderer* m_renderer;
	TransformComponent* m_transform;
	
	//ImageHandling m_image;
	SDL_Texture* m_texture;
	SDL_Rect m_srcR, m_dstR;


public:
	SpriteComponent() = default;
	SpriteComponent(std::string path, SDL_Renderer* renderer) : m_renderer(renderer) {
		//m_image.texture = TextureManager::LoadTexture(path.c_str(), m_renderer);
		m_texture = TextureManager::LoadTexture(path.c_str(), m_renderer);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(m_texture);
	}

	void init() override {
		m_transform = &m_entity->getComponent<TransformComponent>();
		m_srcR.x = m_srcR.y = 0;

		m_srcR.w = m_transform->getWidth();
		m_srcR.h = m_transform->getHeight();
		m_dstR.w = m_transform->getWidth();
		m_dstR.h = m_transform->getHeight();
		//m_image.srcR.x = m_image.srcR.y = 0;
		//m_image.srcR.w = TextureManager::w_texture_dimension;
		//m_image.srcR.h = TextureManager::h_texture_dimension;
		//m_image.dstR.w = TextureManager::w_texture_dimension;
		//m_image.dstR.h = TextureManager::h_texture_dimension;
	}

	//void update(SDL_Event* m_event) override {
	void update() override {
		m_dstR.x = static_cast<int>(m_transform->x());
		m_dstR.y = static_cast<int>(m_transform->y());
		m_dstR.w = m_transform->getWidth() * m_transform->getScale();
		m_dstR.h = m_transform->getHeight() * m_transform->getScale();
		
		//look into future
		//m_image.dstR.x = static_cast<int>(m_transform->getPosition().x);
		//m_image.dstR.y = static_cast<int>(m_transform->getPosition().y);
		//m_image.dstR.w = m_transform->getwidth() * m_transform->getscale();
		//m_image.dstR.h = m_transform->getheight() * m_transform->getscale();
	}

	void draw(SDL_Renderer* renderer) override {
		TextureManager::Draw(
			//m_image.texture, m_image.srcR, m_image.dstR, m_renderer);
			m_texture, m_srcR, m_dstR, m_renderer);
	}

	void resetTexture(std::string path) {
		//m_image.texture = TextureManager::loadTexture(path.c_str(), m_renderer);
		m_texture = TextureManager::LoadTexture(path.c_str(), m_renderer);
	}


};
