#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"
#include "Ball.h"
#include "Paddle.h"
#include "PlayerScore.h"
#include <array>


class GameScene : public Scene
{

public:
	GameScene() :
		mGWindow_(nullptr),
		mGRenderer_(nullptr),
		mScoreFont_(nullptr)
	{

	}
	bool InitializeComp() override;
	void SetScene(Widget&, Widget&,
		Widget&, SDL_Texture&);
	TTF_Font* GetScoreFont() { return mScoreFont_; }
	SDL_Window* GetGameSceneWindow() { return mGWindow_; }
	SDL_Renderer* GetRenderer() { return mGRenderer_; }

	~GameScene();
private:
	SDL_Window* mGWindow_;
	SDL_Renderer* mGRenderer_;
	TTF_Font* mScoreFont_;
};

#endif
