#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>

class ColliderComponent;

class Game {
	std::string m_title;
	bool m_isRunning = false, m_fullscreen;
	int m_x_window_pos, m_y_window_pos, m_window_width, m_window_height;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	long long cnt;

public:
	static SDL_Event game_event;
	static std::vector<ColliderComponent*> m_colliders;

	Game();
	~Game();
	void init(const std::string title = "Game", int x_window_pos = SDL_WINDOWPOS_CENTERED, int y_window_pos = SDL_WINDOWPOS_CENTERED,
		int window_width = 1600, int window_height = 900, bool fullscreen = false);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
};
