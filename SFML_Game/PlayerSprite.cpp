#include "PlayerSprite.h"
#include "stdafx.h"

void PlayerSprite::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void PlayerSprite::initTexture()
{
	if (!this->textureSheet.loadFromFile("Satoshi.png"))
	{
		std::cout << "Can't Load Player Sheet\n";
	}
}

void PlayerSprite::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 64, 64);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(1.2f, 1.2f);
}

void PlayerSprite::initAnimation()
{
	this->animationTimer.restart();
}

PlayerSprite::PlayerSprite()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
}

PlayerSprite::~PlayerSprite()
{

}

void PlayerSprite::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->sprite.move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->sprite.move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		this->sprite.move(0.f, -1.f);	
		this->animState = PLAYER_ANIMATION_STATES::MOVING_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		this->sprite.move(0.f, 1.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
	}
}

void PlayerSprite::updateAnimation()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5f)
		{
			this->currentFrame.top = 256.0f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 256.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 128.0f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 256.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 64.0f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 256.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_UP)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 192.0f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 256.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_DOWN)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 0.0f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 256.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	
	
}

void PlayerSprite::update()
{
	this->updateMovement();
	this->updateAnimation();
}

void PlayerSprite::render(sf::RenderTarget & target)
{
	target.draw(this->sprite);
}
