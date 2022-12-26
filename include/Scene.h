#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class Widget;

class Scene
{
public:
	Scene() :
		mWImp_(nullptr)
	{
	}
	virtual bool InitializeComp();
	virtual ~Scene() {}

protected:
	Widget* mWImp_;
};

#endif
