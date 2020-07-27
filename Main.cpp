#include <iostream>
#include "Game.h"

int main()
{
	Game game;

	if (game.Initialize() == false)
	{
		return 1;
	}

	if (game.Play() == false)
	{
		return 1;
	}

	std::cout << game.getTrackedCellGreenTimes() << std::endl;

	return 0;
}