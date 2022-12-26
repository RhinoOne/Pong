#ifndef BALL_H
#define BALL_H

#include "Vec2D.h"
#include "Widget.h"
#include "Observer.h"
#include "Subject.h"
#include "FrameTime.h"

class Paddle;

class Ball : public Widget, public Observer
{
public:
	Ball(Vec2D, Vec2D, FrameTime*);
	void Update(Subject*, float dt);
	float GetYPos() { return mPosition_.GetY(); }
	float GetXPos() { return mPosition_.GetX(); }

	friend class Collision;

protected:
	SDL_Rect* draw() override;

private:
	Vec2D mPosition_, mSpeed_;
	SDL_Rect mRect_{};
	FrameTime* mSubject_;
	const int mBallH_ = 15;
	const int mBallW_ = 15;
};

#endif

