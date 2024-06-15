#pragma once
#include "Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class ColliderComponent : public Component {
	SDL_Rect m_collider;
	std::string m_tag;

	TransformComponent *m_transform;

public:
	ColliderComponent() {
		this->init();
	}

	ColliderComponent(std::string tag) : m_tag(tag) {

	}

	void init() override {
		if (!m_entity->hasComponent<TransformComponent>()) {
			//m_entity->addComponent<TransformComponent>();
			// 
			throw std::exception();
		//THROW AN ERROR HERE
			//COLLIDER POSITION UPDATE IS INIT_ORDER-SENTENSIVE
		//THROW AN ERROR HERE
			//COLLIDER POSITION UPDATE IS INIT_ORDER-SENTENSIVE
		//THROW AN ERROR HERE
			//COLLIDER POSITION UPDATE IS INIT_ORDER-SENTENSIVE
		//THROW AN ERROR HERE
			//COLLIDER POSITION UPDATE IS INIT_ORDER-SENTENSIVE
		//THROW AN ERROR HERE
			//COLLIDER POSITION UPDATE IS INIT_ORDER-SENTENSIVE
		}
		m_transform = &m_entity->getComponent<TransformComponent>();
		Game::m_colliders.push_back(this);
	}

	void update() override {
		if (m_tag != "terrain") {
			m_collider.x = static_cast<int>(m_transform->x());
			m_collider.y = static_cast<int>(m_transform->y());
			m_collider.w = m_transform->getWidth() * m_transform->getScale();
			m_collider.h = m_transform->getHeight() * m_transform->getScale();
		}
	}

	const SDL_Rect& getCollider() const { return m_collider; }
	const std::string& getTag()const { return m_tag; }
};