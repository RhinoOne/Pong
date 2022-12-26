#include "..\include\MenuScene.h"
#include "..\include\Constant.h"

using namespace constants;

bool Menu::InitializeComp()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
	{
		std::cerr << "Unable to initialize SDL : "
			<< SDL_GetError() << std::endl;
		return false;
	}
	else if (TTF_Init() == -1)
	{
		std::cerr << "Unable to initialize TTF: "
			<< TTF_GetError() << std::endl;
		return false;
	}

	mMWindow_ = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (mMWindow_ == nullptr)
	{
		std::cerr << "Unable to create SDL window: " << SDL_GetError() << std::endl;
		return false;
	}
	mMRenderer_ = SDL_CreateRenderer(mMWindow_, -1, 0);
	if (mMRenderer_ == nullptr)
	{
		std::cerr << "Unable to create SDL renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Menu::SetScene()
{
	mFont_ = TTF_OpenFont("Font\\Undertale-Battle-Font.ttf", 40);
	for(unsigned int key = 0; key != 4; ++key)
	{
		mMItemSurface_[key] = TTF_RenderText_Solid(mFont_, mMlabel_[key], mMcolor_[0]);
		mMItemTexture_[key] = SDL_CreateTextureFromSurface(mMRenderer_, mMItemSurface_[key]);
	}
	for(unsigned int key = 0; key != 4; ++key)
	{
		int widthScore, heightScore;
		SDL_QueryTexture(mMItemTexture_[key], nullptr, nullptr, &widthScore, &heightScore);

		mRectPos_[key].x = constants::WINDOW_WIDTH / 2 - (widthScore / 2);
		mRectPos_[key].y = constants::WINDOW_HEIGHT / 4 + (key * 100);
		mRectPos_[key].w = widthScore;
		mRectPos_[key].h = heightScore;

		SDL_RenderCopy(mMRenderer_, mMItemTexture_[key], nullptr, &mRectPos_[key]);
	}
}

void Menu::CheckChangeColor()
{
	for (unsigned key = 1; key != 4; ++key)
	{
		if(mPosition_.GetX() >= mRectPos_[key].x &&
			mPosition_.GetX() <= mRectPos_[key].x + mRectPos_[key].w &&
			mPosition_.GetY() >= mRectPos_[key].y &&
			mPosition_.GetY() <= mRectPos_[key].y + mRectPos_[key].h)
		{
			if(!mMSelectedItem_[key])
			{
				mMSelectedItem_[key] = true;
				SDL_FreeSurface(mMItemSurface_[key]);
				mMItemSurface_[key] = TTF_RenderText_Solid(mFont_, mMlabel_[key], mMcolor_[1]);

				mMItemTexture_[key] = SDL_CreateTextureFromSurface(mMRenderer_, mMItemSurface_[key]);
				SDL_RenderCopy(mMRenderer_, mMItemTexture_[key], nullptr, &mRectPos_[key]);
			}
		}
		else if (mMSelectedItem_[key])
		{
			mMSelectedItem_[key] = false;
			SDL_FreeSurface(mMItemSurface_[key]);
			mMItemSurface_[key] = TTF_RenderText_Solid(mFont_, mMlabel_[key], mMcolor_[0]);

			mMItemTexture_[key] = SDL_CreateTextureFromSurface(mMRenderer_, mMItemSurface_[key]);
			SDL_RenderCopy(mMRenderer_, mMItemTexture_[key], nullptr, &mRectPos_[key]);
		}
	}
}

Menu::~Menu()
{
	for(unsigned int key = 0; key != mMItemSurface_.size(); ++key)
	{
		SDL_FreeSurface(mMItemSurface_[key]);
		SDL_DestroyTexture(mMItemTexture_[key]);
	}
	SDL_DestroyRenderer(mMRenderer_);
	SDL_DestroyWindow(mMWindow_);
	TTF_CloseFont(mFont_);
	TTF_Quit();
	SDL_Quit();
}

ItemMenu Menu::CheckButtonClick()
{
	for (unsigned key = 1; key != 4; ++key)
	{
		if (mPosition_.GetX() >= mRectPos_[key].x &&
			mPosition_.GetX() <= mRectPos_[key].x + mRectPos_[key].w &&
			mPosition_.GetY() >= mRectPos_[key].y &&
			mPosition_.GetY() <= mRectPos_[key].y + mRectPos_[key].h)
		{
			return ItemMenu(key);
		}
	}
	return ItemMenu::NotSelected;

}