#ifndef GAME_H
#define GAME_H

#include "GameScene.h"
#include "MenuScene.h"
#include "Subject.h"
#include "FrameTime.h"
#include "Collision.h"
#include <chrono>

class Game
{
public:
	Game() :
		mRunning_(true)
	{

	}

	void PVEGameModeEvent(SDL_Event&);
	void PVEGameModeSetting(Paddle&, Paddle&, Ball&);
	void PVPGameModeEvent(SDL_Event&);
	void PVPGameModeSetting(Paddle&, Paddle&, Ball&);

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game() {}
	void Start();
private:
	bool mRunning_;
};

#endif