#ifndef VEC_2D_H
#define VEC_2D_H

class Vec2D
{
public:
	Vec2D() :
		x(0.0f), y(0.0f)
	{}

	Vec2D(float x, float y) :
		x(x), y(y)
	{}

	Vec2D operator+(Vec2D const& rhs)
	{
		return Vec2D(x + rhs.x, y + rhs.y);
	}
	Vec2D& operator+=(Vec2D const& rhs);

	Vec2D operator*(float rhs)
	{
		return Vec2D(x * rhs, y * rhs);
	}

	float GetX() { return x; }
	float GetY() { return y; }
	void SetX(float xValue) { x = xValue; }
	void SetY(float yValue) { y = yValue; }

	friend class Collision;

private:
	float x, y;
};

#endif

