#include"stdafx.h"
#pragma once

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class PlayerSprite
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	//Animation
	short animState;
	sf::IntRect currentFrame;

	//Physics

	//Core

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();

public:
	PlayerSprite();
	virtual ~PlayerSprite();


	//Function
	void updateMovement();
	void updateAnimation();
	void update();
	void render(sf::RenderTarget & target);
};

