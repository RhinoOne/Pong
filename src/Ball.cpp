#include "..\include\Ball.h"

Ball::Ball(Vec2D position, Vec2D speed, FrameTime* frame) :
	mPosition_(position), mSpeed_(speed)
{
	mSubject_ = frame;
	mSubject_->Attach(this);

	mRect_.x = static_cast<int>(mPosition_.GetX());
	mRect_.y = static_cast<int>(mPosition_.GetY());
	mRect_.w = mBallW_;
	mRect_.h = mBallH_;
}

SDL_Rect* Ball::draw()
{
	mRect_.x = static_cast<int>(mPosition_.GetX());
	mRect_.y = static_cast<int>(mPosition_.GetY());
	return &mRect_;
}

void Ball::Update(Subject* changedSub, float dt)
{
	if (changedSub == mSubject_)
		mPosition_ += mSpeed_ * dt;
}
