#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(512,512), "Ice Wall Walk", sf::Style::Fullscreen);
	sf::Texture playerTexture;
	
	playerTexture.loadFromFile("FinSprite.png");

	Player player(&playerTexture, sf::Vector2u(4, 8), 0.2f, 50.0f);
	
	Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(1000.0f, 0.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));
	
	float deltaTime = 0.0f;
	sf::Clock clock;
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		player.Update(deltaTime);
		
		
		Collider playerCollision = player.GetCollider();
		platform1.GetCollider().CheckCollision(playerCollision, 0.0f);
		platform2.GetCollider().CheckCollision(playerCollision, 1.0f);
		
		/*
		platform1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
		platform2.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		*/

		std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
		window.clear();	
		
		player.Draw(window);
		platform1.Draw(window);
		platform2.Draw(window);
		
		window.display();
	}

	return 0;
}