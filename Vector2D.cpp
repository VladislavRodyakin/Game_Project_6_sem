#include "Vector2D.hpp"
#include <iostream>

Vector2D::Vector2D() {
	m_x = 0.0f;
	m_y = 0.0f;
}

Vector2D::Vector2D(float m_x, float m_y) {
	this->m_x = m_x;
	this->m_y = m_y;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
	this->m_x += vec.m_x;
	this->m_y += vec.m_y;
	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec) {
	this->m_x -= vec.m_x;
	this->m_y -= vec.m_y;
	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	this->m_x *= vec.m_x;
	this->m_y *= vec.m_y;
	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec) {
	this->m_x /= vec.m_x;
	this->m_y /= vec.m_y;
	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {	return v1.Add(v2); }

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) { return v1.Subtract(v2); }

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) { return v1.Multiply(v2); }

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) { return v1.Divide(v2); }

Vector2D& Vector2D::operator+=(const Vector2D& vec) { return this->Add(vec); }

Vector2D& Vector2D::operator-=(const Vector2D& vec) { return this->Subtract(vec); }

Vector2D& Vector2D::operator*=(const Vector2D& vec) { return this->Multiply(vec); }

Vector2D& Vector2D::operator/=(const Vector2D& vec) { return this->Divide(vec); }

Vector2D& Vector2D::operator*(const int& i) {
	this->m_x *= i;
	this->m_y *= i;
	return *this;
}

Vector2D& Vector2D::Zero() {
	this->m_x = 0;
	this->m_y = 0;
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
	stream << "(" << vec.m_x << ", " << vec.m_y << ")";
	return stream;
}