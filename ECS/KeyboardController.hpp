#pragma once
#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class SpriteComponent; //there it is again
// maybe has something to do with the order of initialisation in Components.hpp

class KeyboardController : public Component {
	TransformComponent* m_position = nullptr;
	SpriteComponent* m_sprite = nullptr;
public:

	void init() override;
	void update() override;
};