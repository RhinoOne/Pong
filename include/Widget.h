#ifndef WIDGET_H
#define WIDGET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Widget
{
public:
	virtual SDL_Rect* draw() = 0;
};

#endif

