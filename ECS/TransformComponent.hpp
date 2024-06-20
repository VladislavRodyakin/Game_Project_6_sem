#pragma once
#include "ECS.hpp"
#include "../TextureManager.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component {
	Vector2D m_position = {0,0}, m_velocity = {0,0};

	int m_height = TextureManager::h_texture_dimension;
	int m_width = TextureManager::w_texture_dimension;
	
	int m_scale = 1;
	int m_speed = 3;
	bool m_blocked = false;
public:
	/*TransformComponent(int scale) {
		m_position.x(400);
		m_position.y(320);
	}*/

	TransformComponent() = default;
	TransformComponent(float x, float y);
	TransformComponent(float x, float y, int h, int w, int sc);

	// is it even worth it moving such small functions into .cpp?
	// or is it that we only copy the header and not a single ounce of realisation?
	float x() const;
	void x(float x);
	float y() const;
	void y(float y);

	float velocity_x();
	void velocity_x(float x);
	float velocity_y();
	void velocity_y(float y);

	int getWidth();
	int getHeight();
	int getScale();

	int getSpeed();

	void setWidth(int width);
	void setHeight(int height);
	void setScale(int scale);

	void init() override;
	void update() override;

	void setPosition(float x, float y);
	void setPosition(const Vector2D& pos);

	const Vector2D& getPosition();
	const Vector2D& getVelocity();

	void setVelocity(const Vector2D& vel);
	void addToPos(const Vector2D& add_vec);
};