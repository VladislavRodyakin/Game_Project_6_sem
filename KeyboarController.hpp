#pragma once
#include "Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"


class KeyboardController : public Component
{
public:
	TransformComponent* m_position;
	SpriteComponent* m_sprite;

	void init() override{
		m_position = &m_entity->getComponent<TransformComponent>();
		m_sprite = &m_entity->getComponent<SpriteComponent>();
	}

	//void update(SDL_Event* m_event) override {
	void update() override {
		SDL_Event* m_event = &Game::game_event;
		if (m_event->type == SDL_KEYDOWN)
		{
			switch (m_event->key.keysym.sym)
			{
			case SDLK_w:
				m_position->velocity_y(-1);
				break;
			case SDLK_a:
				m_position->velocity_x(-1);
				break;
			case SDLK_d:
				m_position->velocity_x(1);
				break;
			case SDLK_s:
				m_position->velocity_y(1);
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
				break;
			case SDLK_a:
				m_position->velocity_x(0);
				break;
			case SDLK_d:
				m_position->velocity_x(0);
				break;
			case SDLK_s:
				m_position->velocity_y(0);
				break;
			default:
				break;
			}
		}
	}
	void draw(SDL_Renderer* renderer) { return; }
};