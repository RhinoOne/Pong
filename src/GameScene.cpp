#include "..\include\GameScene.h"
#include "..\include\Constant.h"

using namespace constants;


bool GameScene::InitializeComp()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	mGWindow_ = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (mGWindow_ == nullptr)
	{
		std::cerr << "Unable to create SDL window: " << SDL_GetError() << std::endl;
		return false;
	}
	mGRenderer_ = SDL_CreateRenderer(mGWindow_, -1, 0);
	if (mGRenderer_ == nullptr)
	{
		std::cerr << "Unable to create SDL renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	mScoreFont_ = TTF_OpenFont("Font\\Undertale-Battle-Font.ttf", 40);
	if (mScoreFont_ == nullptr) {
		std::cerr << "Unable to load a font for the application: " << TTF_GetError() << std::endl;
	}
	return true;
}
void GameScene::SetScene(Widget& ball, Widget& paddOne,
	Widget& paddTwo, SDL_Texture& tempTexture)
{

	SDL_SetRenderDrawColor(mGRenderer_, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(mGRenderer_);
	SDL_SetRenderDrawColor(mGRenderer_, 0xFF, 0xFF, 0xFF, 0xFF);

	for (int key = 0; key < constants::WINDOW_HEIGHT; key += 5)
		SDL_RenderDrawPoint(mGRenderer_, constants::WINDOW_WIDTH / 2, key);//draw line

	mWImp_ = &ball;
	SDL_RenderFillRect(mGRenderer_, const_cast<SDL_Rect*>(mWImp_->draw()));//draw ball

	mWImp_ = &paddTwo;
	SDL_RenderFillRect(mGRenderer_, const_cast<SDL_Rect*>(mWImp_->draw()));//draw paddleOne
	mWImp_ = &paddOne;
	SDL_RenderFillRect(mGRenderer_, const_cast<SDL_Rect*>(mWImp_->draw()));//draw paddleTwo
}

GameScene::~GameScene()
{
	SDL_DestroyRenderer(mGRenderer_);
	SDL_DestroyWindow(mGWindow_);
	TTF_CloseFont(mScoreFont_);
	Mix_Quit();
}
