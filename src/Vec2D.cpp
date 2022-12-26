#include "..\include\Vec2D.h"
Vec2D& Vec2D::operator+=(Vec2D const& rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}
