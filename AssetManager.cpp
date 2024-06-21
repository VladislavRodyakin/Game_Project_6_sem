#include "AssetManager.hpp"
#include "ECS/Components.hpp"
#include <random>

AssetManager::AssetManager(Manager* manager) :
	m_manager(manager){

}

AssetManager::~AssetManager() {
}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D direction, int range, int speed, const std::string& texture_id, SDL_Renderer* renderer) {
	auto& projectile(m_manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x(), pos.y(), TextureManager::h_texture_dimension, TextureManager::w_texture_dimension, 1);
	projectile.addComponent<SpriteComponent>(texture_id, false, renderer);
	projectile.addComponent<ProjectileComponent>(range, speed, direction);
	projectile.addComponent<ColliderComponent>("projectile",renderer);
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::CreateProjectileRandom(int min_pos, int max_pos, int min_speed, int max_speed, const std::string& texture_id, SDL_Renderer* renderer)
{
	std::random_device pos_rng_dev;
	std::random_device dir_rng_dev;
	std::random_device speed_rng_dev;
	std::mt19937 pos_rng(pos_rng_dev());
	std::mt19937 dir_rng(dir_rng_dev());
	std::mt19937 speed_rng(speed_rng_dev());
	std::uniform_int_distribution<std::mt19937::result_type> position_rng(min_pos, max_pos); 
	std::uniform_int_distribution<std::mt19937::result_type> direction_rng(1, 1000); 
	std::uniform_int_distribution<std::mt19937::result_type> movespeed_rng(min_speed, max_speed);
	CreateProjectile(
		Vector2D{ static_cast<float>(position_rng(pos_rng)), static_cast<float>(position_rng(pos_rng)) },
		Vector2D{ 
			static_cast<float>(static_cast<int>(direction_rng(dir_rng) - 500)) / 1000,
			static_cast<float>(static_cast<int>(direction_rng(dir_rng) - 500)) / 1000
		},
		20000, movespeed_rng(speed_rng), "projectile", renderer);

}

void AssetManager::AddTexture(const std::string& id, const std::string& path, SDL_Renderer* renderer) {
	m_textures[id] = TextureManager::LoadTexture(path, renderer);
}

SDL_Texture* AssetManager::GetTexture(const std::string& id) {
	return m_textures[id];
}

void AssetManager::AddFont(const std::string& id, const std::string& path, int size) {
	m_fonts[id] = TTF_OpenFont(path.c_str(), size);
}

TTF_Font* AssetManager::GetFont(const std::string& id)
{
	return m_fonts[id];
}
