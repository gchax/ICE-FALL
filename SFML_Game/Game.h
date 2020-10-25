#pragma once
#include "stdafx.h"
#include "PlayerSprite.h"
class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;
	
	PlayerSprite* player;

	void initWindow();
	void initPlayer();

public:

	//Functions

	Game();
	virtual ~Game();

	//Functions
	void updatePlayer();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};

