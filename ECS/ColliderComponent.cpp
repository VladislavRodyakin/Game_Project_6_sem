#include "ColliderComponent.hpp"

ColliderComponent::ColliderComponent() {
	this->init();
}

ColliderComponent::ColliderComponent(const std::string& tag, SDL_Renderer* renderer)
	: m_tag(tag), m_renderer(renderer) {
}

ColliderComponent::ColliderComponent(const std::string& tag, int xpos, int ypos, int size, SDL_Renderer* renderer)
	: m_tag(tag), m_renderer(renderer) {
	m_collider.x = xpos;
	m_collider.y = ypos;
	m_collider.h = m_collider.w = size;
}

void ColliderComponent::init() {
	if (!m_entity->hasComponent<TransformComponent>()) {
		m_entity->addComponent<TransformComponent>();
	}

	m_transform = &m_entity->getComponent<TransformComponent>();
	m_src_r = { 0,0,TextureManager::h_texture_dimension,TextureManager::w_texture_dimension };
	m_dst_r = { m_collider.x, m_collider.y, m_collider.h, m_collider.w };
}

void ColliderComponent::update() {
	if (m_tag != "terrain") {
		m_collider.x = static_cast<int>(m_transform->x());
		m_collider.y = static_cast<int>(m_transform->y());
		m_collider.w = m_transform->getWidth() * m_transform->getScale();
		m_collider.h = m_transform->getHeight() * m_transform->getScale();
	}
	m_dst_r.x = m_collider.x - Game::camera_position.x;
	m_dst_r.y = m_collider.y - Game::camera_position.y;
}

void ColliderComponent::draw() {
	TextureManager::Draw(m_texture, m_src_r, m_dst_r, m_renderer);
}

const SDL_Rect& ColliderComponent::getCollider() const {
	return m_collider; 
}

const std::string& ColliderComponent::getTag() const { 
	return m_tag;
}