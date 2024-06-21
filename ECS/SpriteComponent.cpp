#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(std::string path, SDL_Renderer* renderer)
	: m_renderer(renderer) {
	m_texture = TextureManager::LoadTexture(path.c_str(), m_renderer);
}

SpriteComponent::SpriteComponent(std::string texture_id, bool is_animated, SDL_Renderer* renderer)
	: m_renderer(renderer) {
	m_texture = Game::m_asset_manager.GetTexture(texture_id);
	m_is_animated = true;

	Animation idle = Animation(0, 4, 100);
	Animation fly = Animation(1, 6, 30);

	m_animations["Idle"] = idle;
	m_animations["Fly"] = fly;

	play("Idle");
}

SpriteComponent::~SpriteComponent() {
}

void SpriteComponent::init() {
	m_transform = &m_entity->getComponent<TransformComponent>();
	m_srcR.x = m_srcR.y = 0;

	m_srcR.w = m_transform->getWidth();
	m_srcR.h = m_transform->getHeight();
	m_dstR.w = m_transform->getWidth();
	m_dstR.h = m_transform->getHeight();
}

void SpriteComponent::update() {
	if (m_is_animated) {
		m_srcR.x = m_srcR.w * static_cast<int>((SDL_GetTicks() / m_frame_time) % m_frames);
	}
	m_dstR.x = static_cast<int>(m_transform->x()) - Game::camera_position.x;
	m_dstR.y = static_cast<int>(m_transform->y()) - Game::camera_position.y;
	m_dstR.w = m_transform->getWidth() * m_transform->getScale();
	m_dstR.h = m_transform->getHeight() * m_transform->getScale();

	m_srcR.y = m_anim_id * m_transform->getHeight();

}

void SpriteComponent::setFlip(SDL_RendererFlip flip) {
	m_sprite_flip = flip;
}

void SpriteComponent::draw() {
	TextureManager::Draw(
		m_texture, m_srcR, m_dstR, m_renderer, m_sprite_flip);
}

void SpriteComponent::resetTexture(std::string texture_id) {
	m_texture = Game::m_asset_manager.GetTexture(texture_id);
}

void SpriteComponent::play(std::string anim_name) {
	m_anim_id = m_animations[anim_name].index;
	m_frames = m_animations[anim_name].frames;
	m_frame_time = m_animations[anim_name].frame_time;
}
