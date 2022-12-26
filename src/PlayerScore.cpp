#include "..\include\PlayerScore.h"
#include <string>
PlayerScore::PlayerScore(Vec2D position, SDL_Renderer* ren, TTF_Font* font) :
	mRenderer_(ren), mFont_(font)
{

	mSurface_ = TTF_RenderText_Solid(mFont_, "0", { 0xFF, 0xFF, 0xFF, 0xFF });
	mTexture_ = SDL_CreateTextureFromSurface(mRenderer_, mSurface_);

	int widthScore, heightScore;
	SDL_QueryTexture(mTexture_, nullptr, nullptr, &widthScore, &heightScore);

	mRect_.x = static_cast<int>(position.GetX());
	mRect_.y = static_cast<int>(position.GetY());
	mRect_.w = widthScore;
	mRect_.h = heightScore;
}
void PlayerScore::SetScore(int score, SDL_Renderer* ren)
{
	SDL_FreeSurface(mSurface_);
	SDL_DestroyTexture(mTexture_);

	mSurface_ = TTF_RenderText_Solid(mFont_, std::to_string(score).c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });
	mTexture_ = SDL_CreateTextureFromSurface(mRenderer_, mSurface_);

	int width, height;
	SDL_QueryTexture(mTexture_, nullptr, nullptr, &width, &height);
	mRect_.w = width;
	mRect_.h = height;
}
PlayerScore::~PlayerScore()
{
	SDL_FreeSurface(mSurface_);
	SDL_DestroyTexture(mTexture_);
}
