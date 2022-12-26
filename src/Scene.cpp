#include "..\include\Scene.h"

bool Scene::InitializeComp()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cerr << "Unable to initialize SDL : "
			<< SDL_GetError() << std::endl;
		return false;
	}
}
