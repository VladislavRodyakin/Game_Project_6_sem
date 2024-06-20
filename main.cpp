#include "SDL.h"
#include "Game.hpp"

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Game game;
	//game.init();

	int frameTime = 0;
	size_t frameStart = 0;
	while (game.running()) {

		frameStart = SDL_GetTicks();

		game.handleEvents();
		game.update();
		game.render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	//Game destructor will call this
	//game.clean(); 
	return 0;
}