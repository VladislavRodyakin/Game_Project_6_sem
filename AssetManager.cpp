#include "AssetManager.hpp"
#include "ECS/Components.hpp"

AssetManager::AssetManager(Manager* manager) :
	m_manager(manager){

}

AssetManager::~AssetManager() {
}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D direction, int range, int speed, std::string texture_id, SDL_Renderer* renderer) {
	auto& projectile(m_manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x(), pos.y(), TextureManager::h_texture_dimension, TextureManager::w_texture_dimension, 1);
	projectile.addComponent<SpriteComponent>(texture_id, false, renderer);
	projectile.addComponent<ProjectileComponent>(range, speed, direction);
	projectile.addComponent<ColliderComponent>("projectile",renderer);
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::AddTexture(std::string id, std::string path, SDL_Renderer* renderer) {
	m_textures[id] = TextureManager::LoadTexture(path, renderer);
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
	return m_textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int size) {
	m_fonts[id] = TTF_OpenFont(path.c_str(), size);
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return m_fonts[id];
}
