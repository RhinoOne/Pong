#include "..\include\Collision.h"
#include "..\include\Constant.h"

using namespace constants;

Collision::Contact Collision::checkPaddleCol(Ball& ball, Paddle& paddle)
{
	float blLeft = ball.mPosition_.x;
	float bRight = ball.mPosition_.x + ball.mBallW_;
	float bTop = ball.mPosition_.y;
	float bBottom = ball.mPosition_.y + ball.mBallH_;

	float pLeft = paddle.mPosition_.x;
	float pRight = paddle.mPosition_.x + paddle.mPaddleW_;
	float pTop = paddle.mPosition_.y;
	float pBottom = paddle.mPosition_.y + paddle.mPaddleH_;

	Collision::Contact contact{};

	if (blLeft >= pRight)
	{
		return contact;
	}

	if (bRight <= pLeft)
	{
		return contact;
	}

	if (bTop >= pBottom)
	{
		return contact;
	}

	if (bBottom <= pTop)
	{
		return contact;
	}

	float paddleRangeUpper = pBottom - (2.0f * paddle.mPaddleH_ / 3.0f);
	float paddleRangeMiddle = pBottom - (paddle.mPaddleH_ / 3.0f);

	if (ball.mSpeed_.x < 0)
		contact.penetration = pRight - blLeft;
	else if (ball.mSpeed_.x > 0)
		contact.penetration = pLeft - bRight;

	if ((bBottom > pTop) && (bBottom < paddleRangeUpper))
		contact.type = CollisionType::Top;
	else if ((bBottom > paddleRangeUpper) && (bBottom < paddleRangeMiddle))
		contact.type = CollisionType::Middle;
	else
		contact.type = CollisionType::Bottom;

	return contact;
}

Collision::Contact Collision::CheckWallCollision(Ball& ball)
{
	float bLeft = ball.mPosition_.x;
	float bRight = ball.mPosition_.x + ball.mBallW_;
	float bTop = ball.mPosition_.y;
	float bBottom = ball.mPosition_.y + ball.mBallH_;

	Collision::Contact contact{};

	if (bLeft < 0.0f)
	{
		contact.type = CollisionType::Left;
	}
	else if (bRight > constants::WINDOW_WIDTH)
	{
		contact.type = CollisionType::Right;
	}
	else if (bTop < 0.0f)
	{
		contact.type = CollisionType::Top;
		contact.penetration = -bTop;
	}
	else if (bBottom > constants::WINDOW_HEIGHT)
	{
		contact.type = CollisionType::Bottom;
		contact.penetration = constants::WINDOW_HEIGHT - bBottom;
	}

	return contact;
}

void Collision::CollideWithPaddle(Contact const& contact, Ball& ball)
{
	ball.mPosition_.x += contact.penetration;
	ball.mSpeed_.x = -ball.mSpeed_.x;

	if (contact.type == CollisionType::Top)
		ball.mSpeed_.y = -.75f * constants::BALL_SPEED;
	else if (contact.type == CollisionType::Bottom)
		ball.mSpeed_.y = 0.75f * constants::BALL_SPEED;
}
void Collision::CollideWithWall(Contact const& contact, Ball& ball)
{
	if ((contact.type == CollisionType::Top)
		|| (contact.type == CollisionType::Bottom))
	{
		ball.mPosition_.y += contact.penetration;
		ball.mSpeed_.y = -ball.mSpeed_.y;
	}
	else if (contact.type == CollisionType::Left)
	{
		ball.mPosition_.x = constants::WINDOW_WIDTH / 2.0f;
		ball.mPosition_.y = constants::WINDOW_HEIGHT / 2.0f;
		ball.mSpeed_.x = constants::BALL_SPEED;
		ball.mSpeed_.y = 0.75f * constants::BALL_SPEED;
	}
	else if (contact.type == CollisionType::Right)
	{
		ball.mPosition_.x = constants::WINDOW_WIDTH / 2.0f;
		ball.mPosition_.y = constants::WINDOW_HEIGHT / 2.0f;
		ball.mSpeed_.x = -constants::BALL_SPEED;
		ball.mSpeed_.y = 0.75f * constants::BALL_SPEED;
	}
}
