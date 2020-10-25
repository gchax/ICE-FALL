#include "PlayerSprite.h"
#include "stdafx.h"

void PlayerSprite::initTexture()
{
}

void PlayerSprite::initSprite()
{
}

PlayerSprite::PlayerSprite()
{
	this->initTexture();
	this->initSprite();
}

PlayerSprite::~PlayerSprite()
{

}

void PlayerSprite::update()
{

}

void PlayerSprite::render(sf::RenderTarget & target)
{
	target.draw(this->sprite);
}
