#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include <sstream>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "stdafx.h"

int main()
{
	Game game;

	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}


	return 0;
}