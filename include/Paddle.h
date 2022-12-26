#ifndef PADDLE_H
#define PADDLE_H

#include "Vec2D.h"
#include "Widget.h"
#include "Subject.h"
#include "FrameTime.h"

class Paddle : public Widget, public Observer
{
public:
	Paddle(Vec2D, Vec2D, FrameTime*);

	void Update(Subject*, float);
	float getSpeed() { return mSpeed_.GetY(); }
	void setSpeed(float speedValue) { mSpeed_.SetY(speedValue); }
	float getYPos() { return mPosition_.GetY(); }
	float getXPos() { return mPosition_.GetX(); }

	friend class Collision;

protected:
	SDL_Rect* draw() override;

private:
	Vec2D mPosition_, mSpeed_;
	SDL_Rect mRect_{};
	FrameTime* mSubject_;
	const int mPaddleH_ = 100;
	const int mPaddleW_ = 10;
};

#endif
