#include "SDL.h"
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"

Manager manager;
SDL_Event Game::game_event;
SDL_Rect Game::camera_position;
AssetManager Game::m_asset_manager{ &manager };

// which one is better to use?
//#define TERRAIN_TILE_PATH "assets/terrain_tiles.png" 
const std::string TERRAIN_TILE_PATH = "assets/terrain_tiles.png";
const std::string CONTROLS_TEXT = "Move with WASD, ESC to quit";

std::vector<ColliderComponent*> Game::m_colliders;

auto& new_player(manager.addEntity());
auto& position_label(manager.addEntity());
auto& score_label(manager.addEntity());
auto& commands_label(manager.addEntity());


Game::Game(const std::string& title, int x_window_pos, int y_window_pos,
	int window_width, int window_height, bool fullscreen) : 
	m_title(title), m_x_window_pos(x_window_pos), m_y_window_pos(y_window_pos),
	m_window_width(window_width), m_window_height(window_height), m_fullscreen(fullscreen)
{
	init(title, x_window_pos, y_window_pos, window_width, window_height, fullscreen);
}

Game::~Game() {
	clean();
}

void Game::init(const std::string& title, int x_window_pos, int y_window_pos, int window_width, int window_height, bool fullscreen) {
	m_count = 0;
	camera_position.x = camera_position.y = 0;
	camera_position.w = window_width/2;
	camera_position.h = window_height/2;
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Initialistaion error!" << std::endl;
		return;
	}
	m_window = SDL_CreateWindow(title.c_str(), x_window_pos, y_window_pos, window_width, window_height, flags);
	if (!m_window) {
		std::cout << "Window is not created" << std::endl;
		return;
	}
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	if (!m_renderer) {
		std::cout << "Renderer is not created" << std::endl;
		return;
	}
	if (TTF_Init() == -1) {
		std::cout << "SDL_TTF failed to init" << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(m_renderer, 
		TextureManager::BLACK.r, 
		TextureManager::BLACK.g, 
		TextureManager::BLACK.b, 
		TextureManager::BLACK.a);

	

	m_asset_manager.AddFont("arial_test", "assets/fonts/arial.ttf", 20);

	m_asset_manager.AddTexture("terrain", TERRAIN_TILE_PATH, m_renderer);
	m_asset_manager.AddTexture("player", "assets/test_anim_added.png", m_renderer);
	m_asset_manager.AddTexture("projectile", "assets/projectile_transparent.png", m_renderer);

	Map map{ "terrain", 1, 50, m_renderer };



	position_label.addComponent<UILabel>(650, m_window_height - 40, "Position label", "arial_test", TextureManager::WHITE, m_renderer);
	score_label.addComponent<UILabel>(m_window_width/2 - 50, m_window_height - 40, "Score label", "arial_test", TextureManager::RED, m_renderer);
	commands_label.addComponent<UILabel>(20, m_window_height - 40, CONTROLS_TEXT, "arial_test", TextureManager::WHITE, m_renderer);
	position_label.addGroup(Game::groupLabels);
	score_label.addGroup(Game::groupLabels);
	commands_label.addGroup(Game::groupLabels);

	new_player.addComponent<TransformComponent>();
	new_player.addComponent<ColliderComponent>("player", m_renderer);
	new_player.getComponent<TransformComponent>().setPosition(static_cast<int>(window_width / 2.0), static_cast<int>(window_height / 2.0));
	new_player.getComponent<TransformComponent>().setSpeed(8);
	new_player.addComponent<SpriteComponent>("player", true, m_renderer);
	new_player.addGroup(Game::groupPlayers);
	new_player.addComponent<KeyboardController>();

	m_asset_manager.CreateProjectile(Vector2D{100,100}, Vector2D{ 1,1 }, 20000, 7, "projectile", m_renderer);
	
	map.loadMap("assets/coord_map.map", 20, 17, m_renderer);


	m_isRunning = true;
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& lables(manager.getGroup(Game::groupLabels));


void Game::handleEvents() {
	SDL_PollEvent(&game_event);

	switch (game_event.type) {
	case SDL_QUIT:
		m_isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	if (game_event.type == SDL_KEYUP and game_event.key.keysym.sym == SDLK_ESCAPE) {
		m_isRunning = false;
		return;
	}

	if (projectiles.size() == 0)
	{
		m_asset_manager.CreateProjectileRandom(100, m_window_height - 200, 3, 7, "projectile", m_renderer);
		auto& projectiles(manager.getGroup(Game::groupProjectiles));
	}


	SDL_Rect player_collider = new_player.getComponent<ColliderComponent>().getCollider();
	Vector2D player_previous_position = new_player.getComponent<TransformComponent>().getPosition();
	Vector2D player_velocity = new_player.getComponent<TransformComponent>().getVelocity();
	int player_speed = new_player.getComponent<TransformComponent>().getSpeed();
	cnt++;
	
	std::stringstream string_stream_pos;
	string_stream_pos << "player pos" << player_previous_position;
	position_label.getComponent<UILabel>().SetLabelText(string_stream_pos.str());
	
	std::stringstream string_stream_score;
	string_stream_score << "Score: " << m_count;
	score_label.getComponent<UILabel>().SetLabelText(string_stream_score.str());
	manager.refresh();
	manager.update();

	
	for (auto& collider : colliders) {
		if (Collision::AABB(
			collider->getComponent<ColliderComponent>().getCollider(),
			player_collider)) {

			new_player.getComponent<TransformComponent>().setPosition(player_previous_position);
		}
	}

	for (auto& projectile : projectiles) {
		if (Collision::AABB(
			projectile->getComponent<ColliderComponent>().getCollider(),
			player_collider)) {
			std::cout << "Projectile hit player" << std::endl;
			projectile->destroy();

			m_count++;
		}
	}

}


void Game::render() {
	SDL_RenderClear(m_renderer);
	
	//suboptimal, but any other ways cause crash
	m_groups.clear();
	m_groups.push_back(tiles);		//0
	m_groups.push_back(players);	//1
	m_groups.push_back(projectiles);//2
	m_groups.push_back(enemies);	//3
	m_groups.push_back(colliders);	//4
	m_groups.push_back(lables);		//5

	manager.draw(m_groups);

	SDL_RenderPresent(m_renderer);
}

void Game::clean() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool Game::running() {
	return m_isRunning;
}
