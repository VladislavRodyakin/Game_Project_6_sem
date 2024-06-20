#include "SDL.h"
#include "Game.hpp"

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Game game;

	int frameTime = 0;
	size_t frameStart = 0;
	while (game.running()) {

		frameStart = SDL_GetTicks();

		game.handleEvents();
		game.update();
		game.render();

		frameTime = static_cast<int>(SDL_GetTicks() - frameStart);
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return 0;
}