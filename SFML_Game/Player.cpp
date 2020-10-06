#include "Player.h"
#include "Animation.h"
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceTop = true;

	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	/*Movement in y-axis*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
	    checkGameStart = true;
		movement.y -= speed * deltaTime;
		row = 1;
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		checkGameStart = true;
		movement.y += speed * deltaTime;
		row = 0;
	}


	/*Movement in x-axis*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		checkGameStart = true;
		movement.x -= speed * deltaTime;
		row = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		checkGameStart = true;
		movement.x += speed * deltaTime;
		row = 2;
	}

	//Check Movement
	if (movement.y == 0.0f && movement.x == 0.0f)
	{
		statusWalk = false;
	}
	else
	{
		statusWalk = true;
		if (movement.y < 0.0f)
		{
			faceTop = true;
		}
		else
		{
			faceTop = false;
		}

		if (movement.x < 0.0f)
		{
			faceLeft = true;
		}	
		else
		{
			faceLeft = false;
		}
			
	}

	animation.Update(row, deltaTime, faceTop, faceLeft, statusWalk, checkGameStart);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}