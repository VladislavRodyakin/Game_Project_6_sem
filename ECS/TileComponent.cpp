#include "TileComponent.hpp"

TileComponent::TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const std::string& texture_id, SDL_Renderer* renderer)
	: m_renderer(renderer) {
	m_texture = Game::m_asset_manager.GetTexture(texture_id);

	m_position.x(static_cast<float>(xpos));
	m_position.y(static_cast<float>(ypos));

	m_src_r.x = srcX;
	m_src_r.y = srcY;
	m_src_r.h = tsize;
	m_src_r.w = tsize;

	m_dst_r.x = xpos;
	m_dst_r.y = ypos;
	m_dst_r.h = tsize * tscale;
	m_dst_r.w = tsize * tscale;
}

TileComponent::~TileComponent() {
	SDL_DestroyTexture(m_texture);
}

int TileComponent::getDestX() { return m_dst_r.x; }

void TileComponent::setDestX(int x) { m_dst_r.x = x; }

void TileComponent::addDestX(int x) { m_dst_r.x += x; }

int TileComponent::getDestY() { return m_dst_r.y; }

void TileComponent::setDestY(int y) { m_dst_r.y = y; }

void TileComponent::addDestY(int y) { m_dst_r.y += y; }

void TileComponent::draw() {
	TextureManager::Draw(m_texture, m_src_r, m_dst_r, m_renderer);
}

void TileComponent::update() {
	m_dst_r.x = static_cast<int>(m_position.x()) - Game::camera_position.x;
	m_dst_r.y = static_cast<int>(m_position.y()) - Game::camera_position.y;
}
