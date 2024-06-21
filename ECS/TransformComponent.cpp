#include "TransformComponent.hpp"

TransformComponent::TransformComponent(float x, float y) 
	: m_position(Vector2D(x, y)) {
	m_velocity.Zero();
}

TransformComponent::TransformComponent(float x, float y, int h, int w, int sc)
	: m_position(Vector2D(x, y)), m_height(h), m_width(w), m_scale(sc) {
	m_velocity.Zero();
}

float TransformComponent::x() const {
	return m_position.x();
}

void TransformComponent::x(float x) {
	m_position.x(x);
}

float TransformComponent::y() const {
	return m_position.y();
}

void TransformComponent::y(float y) {
	m_position.y(y);
}

float TransformComponent::velocity_x() {
	return m_velocity.x();
}

void TransformComponent::velocity_x(float x) {
	m_velocity.x(x);
}

float TransformComponent::velocity_y() {
	return m_velocity.y();
}

void TransformComponent::velocity_y(float y) {
	m_velocity.y(y);
}

int TransformComponent::getWidth() {
	return m_width;
}

int TransformComponent::getHeight() {
	return m_height;
}

int TransformComponent::getScale() {
	return m_scale;
}

int TransformComponent::getSpeed() {
	return m_speed;
}

void TransformComponent::setWidth(int width) {
	m_width = width;
}

void TransformComponent::setHeight(int height) {
	m_height = height;
}

void TransformComponent::setScale(int scale) {
	m_scale = scale;
}

void TransformComponent::setSpeed(int speed) {
	m_speed = speed;
}


void TransformComponent::init() {
	m_velocity.Zero();
}

void TransformComponent::update() {
	m_position += Vector2D(m_velocity.x() * m_speed, m_velocity.y() * m_speed);
}

void TransformComponent::setPosition(float x, float y) {
	m_position.x(x);
	m_position.y(y);
}

void TransformComponent::setPosition(const Vector2D& pos) {
	m_position = pos;
}

const Vector2D& TransformComponent::getPosition(){
	return m_position;
}

const Vector2D& TransformComponent::getVelocity() {
	return m_velocity;
}

void TransformComponent::setVelocity(const Vector2D& vel) {
	m_velocity = vel;
}

void TransformComponent::addToPos(const Vector2D& add_vec) {
	m_position += add_vec;
}
