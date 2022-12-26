#include <iostream>
#include "..\include\PongGame.h"


int main(int argc, char* argv[])
{
	PongGame::Instance()->Start();
	return 0;
}
