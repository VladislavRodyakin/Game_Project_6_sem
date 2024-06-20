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
auto& commands_label(manager.addEntity());

//auto& wall(manager.addEntity());
//auto& tile0(manager.addEntity());



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

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	
	m_isRunning = true;

	m_asset_manager.AddFont("arial_test", "assets/fonts/arial.ttf", 20);

	m_asset_manager.AddTexture("terrain", TERRAIN_TILE_PATH, m_renderer);
	m_asset_manager.AddTexture("player", "assets/test_anim_added.png", m_renderer);
	m_asset_manager.AddTexture("projectile", "assets/projectile_transparent.png", m_renderer);

	Map map{ "terrain", 1, 50, m_renderer };


	/*tile2.addComponent<TileComponent>(200, 200, TextureManager::h_texture_dimension, TextureManager::w_texture_dimension, 0, m_renderer);
	tile2.addComponent<ColliderComponent>("asteroids");
	tile2.addGroup(groupColliders);*/
	

	position_label.addComponent<UILabel>(50, 50, "Test label", "arial_test", TextureManager::BLACK, m_renderer);
	commands_label.addComponent<UILabel>(20, m_window_height - 50, CONTROLS_TEXT, "arial_test", TextureManager::BLACK, m_renderer);


	new_player.addComponent<TransformComponent>();
	new_player.addComponent<ColliderComponent>("player", m_renderer);

	//centered player
	new_player.getComponent<TransformComponent>().setPosition(static_cast<int>(window_width / 2.0), static_cast<int>(window_height / 2.0));
	//left-top corner positioned player
	//new_player.getComponent<TransformComponent>().setPosition(75, 75);
	
	new_player.addComponent<SpriteComponent>("player", true, m_renderer);
	new_player.addGroup(Game::groupPlayers);
	new_player.addComponent<KeyboardController>();


	//TODO: make them randomly appear
	

	m_asset_manager.CreateProjectile(Vector2D{100,100}, Vector2D{ 1,1 }, 20000, 5, "projectile", m_renderer);


	/*wall.addGroup(Game::groupColliders);
	wall.addComponent<ColliderComponent>("wall", 215, 255, 50, m_renderer);
	wall.getComponent<TransformComponent>().setHeight(50);
	wall.getComponent<TransformComponent>().setWidth(50);
	wall.addComponent<SpriteComponent>("assets/asteroids_tile.png", m_renderer);*/
	
	map.loadMap("assets/coord_map.map", 13, 15, m_renderer);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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
	std::random_device pos_rng_dev;
	std::random_device dir_rng_dev;
	std::random_device speed_rng_dev;
	std::mt19937 pos_rng(pos_rng_dev());
	std::mt19937 dir_rng(dir_rng_dev());
	std::mt19937 speed_rng(speed_rng_dev());
	std::uniform_int_distribution<std::mt19937::result_type> position_rng(75, 575); // distribution in range [1, 6]
	std::uniform_int_distribution<std::mt19937::result_type> direction_rng(0, 500); // distribution in range [1, 6]
	std::uniform_int_distribution<std::mt19937::result_type> movespeed_rng(0, 20); // distribution in range [1, 6]

	//std::cout << position_rng(pos_rng_dev) << std::endl;
	if (projectiles.size() == 0)
	{
		//PROJECTILE IMMEDEATLY DIES
		m_asset_manager.CreateProjectile(Vector2D{ static_cast<float>(position_rng(pos_rng)), static_cast<float>(position_rng(pos_rng)) }, Vector2D{ static_cast<float>(direction_rng(dir_rng)),static_cast<float>(direction_rng(dir_rng)) }, 20000, movespeed_rng(speed_rng), "projectile", m_renderer);
		std::cout<<projectiles[0]->getComponent<TransformComponent>().getPosition()<<std::endl;
	}


	if (game_event.type == SDL_KEYUP and game_event.key.keysym.sym == SDLK_ESCAPE) {
		m_isRunning = false;
		return;
	}

	std::stringstream string_stream;


	SDL_Rect player_collider = new_player.getComponent<ColliderComponent>().getCollider();
	Vector2D player_previous_position = new_player.getComponent<TransformComponent>().getPosition();
	Vector2D player_velocity = new_player.getComponent<TransformComponent>().getVelocity();
	int player_speed = new_player.getComponent<TransformComponent>().getSpeed();
	cnt++;
	string_stream << "player pos" << player_previous_position;
	position_label.getComponent<UILabel>().SetLabelText(string_stream.str());
	manager.refresh();
	manager.update();

	
	for (auto& collider : colliders) {
		if (Collision::AABB(
			collider->getComponent<ColliderComponent>().getCollider(),
			player_collider)) {

			// try labirynth with and without speed
			new_player.getComponent<TransformComponent>().setPosition(player_previous_position - player_velocity*player_speed);
		}
	}

	for (auto& projectile : projectiles) {
		if (Collision::AABB(
			projectile->getComponent<ColliderComponent>().getCollider(),
			player_collider)) {
			std::cout << "Projectile hit player" << std::endl;
			projectile->destroy();

			//also reset player position
		}
	}


	/*int player_speed = new_player.getComponent<TransformComponent>().getSpeed();

	for (auto& tile : tiles) {
		tile->getComponent<TileComponent>().addDestX(-player_velocity.x() * player_speed);
		tile->getComponent<TileComponent>().addDestY(-player_velocity.y() * player_speed);
	}*/


	//disable this for static camera
	//camera_position.x = static_cast<int>(new_player.getComponent<TransformComponent>().x() - camera_position.w);
	//camera_position.y = static_cast<int>(new_player.getComponent<TransformComponent>().y() - camera_position.h);
	
	if (camera_position.x < 0) {
		camera_position.x = 0;
	}
	if (camera_position.y < 0) {
		camera_position.y = 0;
	}
	if (camera_position.x > camera_position.w) {
		camera_position.x = camera_position.w;
	}
	if (camera_position.y > camera_position.h) {
		camera_position.y = camera_position.h;
	}

	//std::cout << "pla " << playerPos.x() << " " << playerPos.y() << std::endl;
	/*for (auto& it_collider : m_colliders) {
		if (Collision::AABB(new_player.getComponent<ColliderComponent>(), *it_collider)
			and &(new_player.getComponent<ColliderComponent>()) != it_collider) {

			new_player.getComponent<TransformComponent>().setPosition(playerPos);
			std::cout << "player hit collider" << std::endl;
		}
	}*/
}


void Game::render() {
	SDL_RenderClear(m_renderer);
	//map->DrawMap();
	//manager.draw(m_renderer);
	 
	 
	
	//maybe into manager.draw()?
	
	
	for (auto& tile : tiles) {
		tile->draw();
	}
	for (auto& player : players) {
		player->draw();
	}
	for (auto& projectile : projectiles) {
		projectile->draw();
	}
	
	for (auto& enemy : enemies) {
		enemy->draw();
	}
	for (auto& collider : colliders) {
		collider->draw();
	}

	position_label.draw();
	commands_label.draw();

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



//void Game::AddTile(int id, int x, int y, SDL_Renderer* renderer) {
//	auto& tile(manager.addEntity());
//	//tile.addComponent<TileComponent>(x, y, TextureManager::h_texture_dimension, TextureManager::w_texture_dimension, id, renderer);
//	tile.addGroup(groupMap);
//}
//
//void Game::AddTile(int srcX, int srcY, int posX, int posY, SDL_Renderer* renderer) {
//	auto& tile(manager.addEntity());
//	tile.addComponent<TileComponent>(srcX, srcY, posX, posY, TERRAIN_TILE_PATH, renderer);
//	tile.addGroup(groupMap);
//}
