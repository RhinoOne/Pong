#ifndef MENU_H
#define MENU_H

#include "Scene.h"
#include "Vec2D.h"
#include <vector>
#include <array>
#include "..\include\Constant.h"

using namespace constants;

enum ItemMenu
{
	NotSelected,
	PVP,
	PVE,
	Exit
};

class Menu : public Scene
{
public:
	Menu() :
		mMWindow_(nullptr), mMRenderer_(nullptr)
	{

	}
	void SetScene();
	bool InitializeComp() override;
	SDL_Renderer* GetRenderer() { return mMRenderer_; }
	void CheckChangeColor();
	ItemMenu CheckButtonClick();
	SDL_Window* getMenuWindow() { return mMWindow_; };
	void SetYPos(float value) { mPosition_.SetY(value); }
	void SetXPos(float value) { mPosition_.SetX(value); }
	~Menu();

private:
	Vec2D mPosition_;
	std::vector<const char*> mMlabel_ = { "M E N U", "PVP", "PVE", "Exit" };
	std::vector<SDL_Surface*> mMItemSurface_ { 4, nullptr };
	std::vector<SDL_Texture*> mMItemTexture_ { 4, nullptr };
	std::array<bool, 4> mMSelectedItem_ = { 0,0,0,0  };
	std::array<SDL_Rect,4> mRectPos_;

	SDL_Color mMcolor_[2] = { {255,255,255}, {255,0,0} };
	SDL_Window* mMWindow_;
	SDL_Renderer* mMRenderer_;
	TTF_Font* mFont_;

};

#endif

