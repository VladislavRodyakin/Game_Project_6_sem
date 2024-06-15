#pragma once
#include "ECS.hpp"
#include "Vector2D.hpp"

class TransformComponent : public Component {
	Vector2D m_position = {0,0}, m_velocity = {0,0};

	int m_height = TextureManager::h_texture_dimension;
	int m_width = TextureManager::w_texture_dimension;
	
	int m_scale = 1;
	int m_speed = 3;
	bool m_blocked = false;
public:
	TransformComponent() = default;
	TransformComponent(float x, float y) : m_position(Vector2D(x,y)){
		m_velocity.Zero();
	}

	TransformComponent(float x, float y, int h, int w, int sc) : m_position(Vector2D(x, y)), m_height(h), m_width(w), m_scale(sc) {
		m_velocity.Zero();
	}

	float x() const { return m_position.x(); }
	void x(float x) { m_position.x(x); }
	float y() const { return m_position.y(); }
	void y(float y) { m_position.y(y); }

	float velocity_x() { return m_velocity.x(); }
	void velocity_x(float x) { m_velocity.x(x); }
	float velocity_y() { return m_velocity.y(); }
	void velocity_y(float y) { m_velocity.y(y); }

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	int getScale() { return m_scale; }

	void setWidth(int width) { m_width = width; }
	void setHeight(int height) { m_height = height; }
	void setScale(int scale) { m_scale = scale; }

	void init() override {
		m_velocity.Zero();
	}

	void update() override {
		m_position.x(m_position.x() + static_cast<int>(m_velocity.x() * m_speed));
		m_position.y(m_position.y() + static_cast<int>(m_velocity.y() * m_speed));
	}

	void setPosition(float x, float y) {
		m_position.x(x);
		m_position.y(y);
		std::cout << "setpos called " << m_position.x() << " " << m_position.y() << std::endl;
	}

	void setPosition(const Vector2D& pos) {
		m_position = pos;
		std::cout << "setpos called " << m_position.x() << m_position.y() << std::endl;

	}

	const Vector2D& getPosition() {
		return m_position;
	}

	const Vector2D& getVelocity() {
		return m_velocity;
	}

	void addToPos(const Vector2D& add_vec) {
		m_position+=add_vec;
	}
};