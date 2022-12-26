
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "Game.h"
#include "MenuScene.h"

class PongGame
{
public:
	PongGame(const PongGame&) = delete;
	PongGame& operator=(const PongGame&) = delete;
	~PongGame() { delete mInstance_; }
	static PongGame* Instance();
	void Start() { mGame_.Start(); }

protected:
	PongGame() {}

private:
	static PongGame* mInstance_;
	Game mGame_;
};

#endif

