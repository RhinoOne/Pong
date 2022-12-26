#include "..\include\PongGame.h"

PongGame* PongGame::mInstance_ = nullptr;
PongGame* PongGame::Instance()
{
	if (mInstance_ == nullptr)
		mInstance_ = new PongGame();

	return mInstance_;
}
