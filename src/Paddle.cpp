#include "..\include\Paddle.h"
#include "..\include\Constant.h"

using namespace constants;

Paddle::Paddle(Vec2D position, Vec2D speed, FrameTime* frame) :
	mPosition_(position), mSpeed_(speed)
{
	mSubject_ = frame;
	mSubject_->Attach(this);

	mPosition_.SetY(mPosition_.GetY() - (mPaddleH_ / 2));

	mRect_.x = static_cast<int>(mPosition_.GetX());
	mRect_.y = static_cast<int>(mPosition_.GetY());
	mRect_.w = mPaddleW_;
	mRect_.h = mPaddleH_;
}

SDL_Rect* Paddle::draw()
{
	mRect_.y = static_cast<int>(mPosition_.GetY());
	return &mRect_;
}
void Paddle::Update(Subject* changedSub, float dt)
{
	if (changedSub == mSubject_)
	{
		mPosition_ += mSpeed_ * dt;

		if (mPosition_.GetY() < 10)
		{
			mPosition_.SetY(10);
		}
		else if (mPosition_.GetY() > ((constants::WINDOW_HEIGHT - 10) - mPaddleH_))
		{
			mPosition_.SetY((constants::WINDOW_HEIGHT - 10) - mPaddleH_);
		}
	}

}
