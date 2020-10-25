#include"stdafx.h"
#pragma once
class PlayerSprite
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	//Animation

	//Movement

	//Core

	void initTexture();
	void initSprite();

public:
	PlayerSprite();
	virtual ~PlayerSprite();


	//Function
	void update();
	void render(sf::RenderTarget & target);
};

