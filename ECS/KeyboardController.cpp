#include "KeyboardController.hpp"

void KeyboardController::init() {
	if (&m_entity->getComponent<TransformComponent>() == nullptr ||
		&m_entity->getComponent<SpriteComponent>() == nullptr) {
		throw std::exception();
	}
	m_position = &m_entity->getComponent<TransformComponent>();
	m_sprite = &m_entity->getComponent<SpriteComponent>();
}

void KeyboardController::update() {
	SDL_Event* m_event = &Game::game_event;
	if (m_event->type == SDL_KEYDOWN)
	{
		switch (m_event->key.keysym.sym)
		{
		case SDLK_w:
			m_position->velocity_y(-1);
			m_sprite->play("Fly");
			break;
		case SDLK_a:
			m_position->velocity_x(-1);
			m_sprite->play("Fly");
			m_sprite->setFlip(SDL_FLIP_HORIZONTAL);
			break;
		case SDLK_d:
			m_position->velocity_x(1);
			m_sprite->play("Fly");
			break;
		case SDLK_s:
			m_position->velocity_y(1);
			m_sprite->play("Fly");
			m_sprite->setFlip(SDL_FLIP_VERTICAL);
			break;
		default:
			break;
		}
	}

	if (m_event->type == SDL_KEYUP)
	{
		switch (m_event->key.keysym.sym)
		{
		case SDLK_w:
			m_position->velocity_y(0);
			m_sprite->play("Idle");
			break;
		case SDLK_a:
			m_position->velocity_x(0);
			m_sprite->play("Idle");
			m_sprite->setFlip(SDL_FLIP_NONE);
			break;
		case SDLK_d:
			m_position->velocity_x(0);
			m_sprite->play("Idle");
			break;
		case SDLK_s:
			m_position->velocity_y(0);
			m_sprite->play("Idle");
			m_sprite->setFlip(SDL_FLIP_NONE);
			break;
		default:
			break;
		}
	}
}