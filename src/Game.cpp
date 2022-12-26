#include "..\include\Game.h"
#include "..\include\Constant.h"

enum Buttons
{
	PaddleOneUp = 0,
	PaddleOneDown,
	PaddleTwoUp,
	PaddleTwoDown
};

bool buttons[4] = {};

void Game::PVEGameModeEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			mRunning_ = false;
		}
		else if (event.key.keysym.sym == SDLK_w)
		{
			buttons[Buttons::PaddleOneUp] = true;
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			buttons[Buttons::PaddleOneDown] = true;
		}
			}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_w)
		{
			buttons[Buttons::PaddleOneUp] = false;
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			buttons[Buttons::PaddleOneDown] = false;
		}
	}
}
void Game::PVEGameModeSetting(Paddle& paddleOne, Paddle& paddleTwo, Ball& ball)
{
	//AI settings
	if (ball.GetYPos() > paddleTwo.getYPos() + 50)
	{
		paddleTwo.setSpeed(0.6f);
	}
	else if (ball.GetYPos() < paddleTwo.getYPos() + 50)
	{
		paddleTwo.setSpeed(-0.6f);
	}
	else
	{
		paddleOne.setSpeed(0.0f);
	}

	//Player settings
	if (buttons[Buttons::PaddleOneUp])
	{
		paddleOne.setSpeed(-constants::PADDLE_SPEED);
	}
	else if (buttons[Buttons::PaddleOneDown])
	{
		paddleOne.setSpeed(constants::PADDLE_SPEED);
	}
	else
	{
		paddleOne.setSpeed(0.0f);
	}
}

void Game::PVPGameModeEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			mRunning_ = false;
		}
		else if (event.key.keysym.sym == SDLK_w)
		{
			buttons[Buttons::PaddleOneUp] = true;
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			buttons[Buttons::PaddleOneDown] = true;
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			buttons[Buttons::PaddleTwoUp] = true;
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			buttons[Buttons::PaddleTwoDown] = true;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_w)
		{
			buttons[Buttons::PaddleOneUp] = false;
		}
		else if (event.key.keysym.sym == SDLK_s)
		{
			buttons[Buttons::PaddleOneDown] = false;
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			buttons[Buttons::PaddleTwoUp] = false;
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			buttons[Buttons::PaddleTwoDown] = false;
		}
	}
}
void Game::PVPGameModeSetting(Paddle& paddleOne, Paddle& paddleTwo, Ball& ball)
{
	//Player settings
	if (buttons[Buttons::PaddleOneUp])
	{
		paddleOne.setSpeed(-constants::PADDLE_SPEED);
	}
	else if (buttons[Buttons::PaddleOneDown])
	{
		paddleOne.setSpeed(constants::PADDLE_SPEED);
	}
	else
	{
		paddleOne.setSpeed(0.0f);
	}

	if (buttons[Buttons::PaddleTwoUp])
	{
		paddleTwo.setSpeed(-constants::PADDLE_SPEED);
	}
	else if (buttons[Buttons::PaddleTwoDown])
	{
		paddleTwo.setSpeed(constants::PADDLE_SPEED);
	}
	else
	{
		paddleTwo.setSpeed(0.0f);
	}
}

void Game::Start()
{

	int p1Score = 0;
	int p2Score = 0;

	ItemMenu menuStatus = ItemMenu::NotSelected;

	Menu mainMenuGame;
	if(mainMenuGame.InitializeComp())
	{
		mainMenuGame.SetScene();

		SDL_Event event;
		while(!menuStatus)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_MOUSEMOTION:
					mainMenuGame.SetXPos(event.motion.x);
					mainMenuGame.SetYPos(event.motion.y);
					mainMenuGame.CheckChangeColor();
					break;
				case SDL_MOUSEBUTTONDOWN:
					menuStatus = mainMenuGame.CheckButtonClick();
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						menuStatus = ItemMenu::Exit;
					}
					break;
				default:
					break;
				}
			}
			SDL_RenderPresent(mainMenuGame.GetRenderer());
		}
		if (menuStatus == ItemMenu::Exit)
			return;
	}

	GameScene currentSceneGame;
	if (!currentSceneGame.InitializeComp())
		return;

	FrameTime frame;
	float dt = 0.0f;

	//ScroeSetting
	TTF_Font* font = TTF_OpenFont("Font\\Undertale-Battle-Font.ttf", 40);
	SDL_Surface* tempSurface = TTF_RenderText_Solid(currentSceneGame.GetScoreFont(), "0", { 0xFF, 0xFF, 0xFF, 0xFF });
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(currentSceneGame.GetRenderer(), tempSurface);

	//Setting sound effects
	Mix_Chunk* paddleHitSoundEffect = Mix_LoadWAV("Sound\\Hit.wav");
	Mix_Chunk* goalSoundEffect = Mix_LoadWAV("Sound\\Goal.wav");

	//Create Widgets
	Ball ball(
		Vec2D((constants::WINDOW_WIDTH / 2.0f),
			(constants::WINDOW_HEIGHT / 2.0f)), Vec2D(constants::BALL_SPEED, 0.0f), &frame);
	Paddle paddleOne(
		Vec2D(50.0f, (constants::WINDOW_HEIGHT / 2.0f)),
		Vec2D(0.0f, 0.0f), &frame);
	Paddle paddleTwo(
		Vec2D(constants::WINDOW_WIDTH - 50.0f, constants::WINDOW_HEIGHT / 2.0f),
		Vec2D(0.0f, 0.0f), &frame);

	PlayerScore playerScoreOne(Vec2D(constants::WINDOW_WIDTH / 4, 20),
		currentSceneGame.GetRenderer(), font);

	PlayerScore playerScoreTwo(Vec2D(3 * constants::WINDOW_WIDTH / 4, 20),
		currentSceneGame.GetRenderer(), font);

	Collision collision;
	SDL_HideWindow(mainMenuGame.getMenuWindow());
	// Start game Logic
	
	while (mRunning_)
	{
		auto startTime = frame.StartTime();

		//Listening to events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (menuStatus)
			{
			case PVP:
				PVPGameModeEvent(event);
				break;
			case PVE:
				PVEGameModeEvent(event);
				break;
			default:
				break;
			}
		}

		switch (menuStatus)
		{
		case PVP:
			PVPGameModeSetting(paddleOne, paddleTwo, ball);
			break;
		case PVE:
			PVEGameModeSetting(paddleOne, paddleTwo, ball);
			break;
		default:
			break;
		}

		frame.Notify(dt);



		//Collision with Paddles
		if (auto cont = collision.checkPaddleCol(ball, paddleOne);
			cont.type != Collision::CollisionType::None)
		{
			collision.CollideWithPaddle(cont, ball);
			Mix_PlayChannel(-1, paddleHitSoundEffect, 0);
		}
		else if (auto cont = collision.checkPaddleCol(ball, paddleTwo);
			cont.type != Collision::CollisionType::None)
		{
			collision.CollideWithPaddle(cont, ball);
			Mix_PlayChannel(-1, paddleHitSoundEffect, 0);
		}
		//Collision with Wall
		else if (auto cont = collision.CheckWallCollision(ball);
			cont.type != Collision::CollisionType::None)
		{
			collision.CollideWithWall(cont, ball);

			//Player score updates
			if (cont.type == Collision::CollisionType::Left)
			{
				++p2Score;
				playerScoreTwo.SetScore(p2Score, currentSceneGame.GetRenderer());
				Mix_PlayChannel(-1, goalSoundEffect, 0);

			}
			else if (cont.type == Collision::CollisionType::Right)
			{
				++p1Score;
				playerScoreOne.SetScore(p1Score, currentSceneGame.GetRenderer());
				Mix_PlayChannel(-1, goalSoundEffect, 0);
			}
		}


		//Widget drawing
		currentSceneGame.SetScene(ball, paddleOne, paddleTwo, *tempTexture);

		//Score player drawing
		playerScoreOne.Draw();
		playerScoreTwo.Draw();


		//Update the screen
		SDL_RenderPresent(currentSceneGame.GetRenderer());

		//Count frames
		auto stopTime = frame.StopTime();
		dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
	}
	Mix_FreeChunk(paddleHitSoundEffect);
	Mix_FreeChunk(goalSoundEffect);
}
