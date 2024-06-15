#pragma once
#include <iostream>

class Vector2D{
	float m_x;
	float m_y;
	
	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

public:

	Vector2D();
	Vector2D(float x, float y);

	float x() const { return m_x; }
	void x(float x) { m_x = x; }
	float y() const { return m_y; }
	void y(float y) { m_y = y; }

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*(const int& i);
	Vector2D& Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};