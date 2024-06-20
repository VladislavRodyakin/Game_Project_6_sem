#pragma once
#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"
#include <iostream>

class ProjectileComponent : public Component {
	TransformComponent* m_transform = nullptr;
	Vector2D m_direction = { 0,0 };
	int m_range = 0, m_speed = 0, m_distance = 0;
public:

	ProjectileComponent(int range, int speed, Vector2D direction);
	~ProjectileComponent();

	void init() override;
	void update() override;
};