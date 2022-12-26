#ifndef PLAYER_SCORE_H
#define PLAYER_SCORE_H

#include "Vec2D.h"
#include "Widget.h"

class PlayerScore
{
public:
	PlayerScore(Vec2D, SDL_Renderer*, TTF_Font*);
	void SetScore(int, SDL_Renderer*);
	void Draw() { SDL_RenderCopy(mRenderer_, mTexture_, nullptr, &mRect_); }
	~PlayerScore();
private:
	SDL_Surface* mSurface_{};
	SDL_Texture* mTexture_{};
	SDL_Renderer* mRenderer_;
	TTF_Font* mFont_;
	SDL_Rect mRect_{};
};

#endif
