#include "ProjectileComponent.hpp"

ProjectileComponent::ProjectileComponent(int range, int speed, Vector2D direction) 
	: m_range(range), m_speed(speed), m_distance(0), m_direction(direction) {

}

ProjectileComponent::~ProjectileComponent()
{
}

void ProjectileComponent::init() {
	m_transform = &m_entity->getComponent<TransformComponent>();
	m_transform->setVelocity(m_direction);
	m_transform->setSpeed(m_speed);
}

void ProjectileComponent::update() {
	if (m_distance > m_range) {
		std::cout << "Projectile exceeded range" << std::endl;
		m_entity->destroy();
	}

	else if (m_transform->x() > Game::camera_position.x + Game::camera_position.w * 2 or
		m_transform->x() < Game::camera_position.x or
		m_transform->y() > Game::camera_position.y + Game::camera_position.h * 2 - 90 or
		m_transform->y() < Game::camera_position.y)
	{
		std::cout << m_transform->getPosition();
		std::cout << "Projectile gone out of bounds" << std::endl;
		m_entity->destroy();
	}

	m_distance += m_speed;
}