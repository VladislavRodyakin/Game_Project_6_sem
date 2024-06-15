#include "SDL.h"
#include <exception>
#include <iostream>
#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

GameObject* player;
GameObject* player2;
Map* map;
SDL_Event Game::game_event;

std::vector<ColliderComponent*> Game::m_colliders;

Manager manager;
auto& new_player(manager.addEntity());
auto& wall(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game(){
}
Game::~Game() {
}

void Game::init(const std::string title, int x_window_pos, int y_window_pos, int window_width, int window_height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Initialistaion error!" << std::endl;
	}
	m_window = SDL_CreateWindow(title.c_str(), x_window_pos, y_window_pos, window_width, window_height, flags);
	if (!m_window) {
		std::cout << "Window is not created" << std::endl;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	if (!m_renderer) {
		std::cout << "Renderer is not created" << std::endl;
	}
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	
	m_isRunning = true;

	map = new Map(15, 10, m_renderer);
	player = new GameObject("assets/test_2.png", m_renderer);
	player2 = new GameObject("assets/test.png", m_renderer, 150, 20);

	tile0.addComponent<TileComponent>(200, 200, TextureManager::h_texture_dimension, TextureManager::w_texture_dimension, 0, m_renderer);
	tile1.addComponent<TileComponent>(250, 250, TextureManager::h_texture_dimension, TextureManager::w_texture_dimension, 1, m_renderer);
	tile2.addComponent<TileComponent>(300, 300, TextureManager::h_texture_dimension, TextureManager::w_texture_dimension, 2, m_renderer);
	tile2.addComponent<TileComponent>(150, 150, TextureManager::h_texture_dimension, TextureManager::w_texture_dimension, 3, m_renderer);
	tile2.addComponent<ColliderComponent>("asteroids");

	new_player.addComponent<TransformComponent>();
	new_player.addComponent<ColliderComponent>("player");
	new_player.addComponent<KeyboardController>();
	new_player.getComponent<TransformComponent>().setPosition(62, 150);
	//new_player.getComponent<TransformComponent>().setScale(2);
	new_player.addComponent<SpriteComponent>("assets/test.png", m_renderer);

	wall.addComponent<TransformComponent>();
	wall.addComponent<ColliderComponent>("wall");
	wall.getComponent<TransformComponent>().setPosition(215,255);
	wall.getComponent<TransformComponent>().setHeight(50);
	wall.getComponent<TransformComponent>().setWidth(55);
	wall.addComponent<SpriteComponent>("assets/asteroids_tile.png", m_renderer);

}

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
	cnt++;
	player->update();
	player2->update();
	Vector2D playerPos = new_player.getComponent<TransformComponent>().getPosition();
	//playerPos -= new_player.getComponent<TransformComponent>().getVelocity();
	manager.refresh();
	/*if (cnt >= 5) {
		Game::game_event.type = SDL_KEYDOWN;
		Game::game_event.key.keysym.sym = SDLK_d;

	}*/
	manager.update();
	std::cout << playerPos.x() << " " << playerPos.y() << std::endl;
	for (auto& it_collider : m_colliders) {

		//if (Collision::AABB(new_player.getComponent<ColliderComponent>(), wall.getComponent<ColliderComponent>())) {
		if (Collision::AABB(new_player.getComponent<ColliderComponent>(), *it_collider)
			and &(new_player.getComponent<ColliderComponent>()) != it_collider) {
		
			std::cout << "col plpos " 
				<< new_player.getComponent<TransformComponent>().getPosition().x()
				<< " " 
				<< new_player.getComponent<TransformComponent>().getPosition().y()
				<< std::endl;

			new_player.getComponent<TransformComponent>().setPosition(playerPos.x(),playerPos.y());
			//new_player.getComponent<TransformComponent>().setPosition(playerPos);
			//new_player.getComponent<TransformComponent>().setPosition(playerPos - new_player.getComponent<TransformComponent>().getVelocity());
			//new_player.getComponent<TransformComponent>().setPosition(0,0);
			std::cout << "player hit collider" << std::endl;
			//new_player.getComponent<SpriteComponent>().resetTexture("assets/asteroids_tile.png");
		}
		else {
			//new_player.getComponent<SpriteComponent>().resetTexture("assets/test.png");
		}

	}
}

void Game::render() {
	SDL_RenderClear(m_renderer);
	//map->DrawMap();
	player->render();
	player2->render();
	manager.draw(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Game::clean() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool Game::running()
{
	return m_isRunning;
}
