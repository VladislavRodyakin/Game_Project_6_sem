#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>
//#include "AssetManager.hpp"

class ColliderComponent;
class AssetManager; // for some reason include didn't work

class Game {
	std::string m_title = "";
	bool m_isRunning = false, m_fullscreen = false;
	int m_x_window_pos = 0, m_y_window_pos = 0, m_window_width = 0, m_window_height = 0;
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	long long cnt = 0;

public:
	enum groupLabels : std::size_t {
		groupMap, groupPlayers, groupEnemies, groupColliders, groupProjectiles
	};

	static SDL_Event game_event;
	static std::vector<ColliderComponent*> m_colliders;
	static SDL_Rect camera_position;
	static AssetManager m_asset_manager;



	Game(const std::string& title = "Game", int x_window_pos = SDL_WINDOWPOS_CENTERED, int y_window_pos = SDL_WINDOWPOS_CENTERED,
		int window_width = 1000, int window_height = 900, bool fullscreen = false);
	~Game();

	void init(const std::string& title = "Game", int x_window_pos = SDL_WINDOWPOS_CENTERED, int y_window_pos = SDL_WINDOWPOS_CENTERED,
		int window_width = 1000, int window_height = 900, bool fullscreen = false);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
};
