#ifndef COLLISION_H
#define COLLISION_H

#include "Paddle.h"
#include "Ball.h"

class Collision
{
public:
	Collision() {}

	enum class CollisionType
	{
		None,
		Top,
		Middle,
		Bottom,
		Left,
		Right
	};
	struct Contact
	{
		CollisionType type;
		float penetration;
	};

	Contact checkPaddleCol(Ball&, Paddle&);
	Contact CheckWallCollision(Ball&);
	void CollideWithPaddle(Contact const&, Ball&);
	void CollideWithWall(Contact const&, Ball&);

};

#endif
