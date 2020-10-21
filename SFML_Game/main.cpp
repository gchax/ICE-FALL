#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Ice Wall Walk", sf::Style::Close | sf::Style::Resize);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("FinSprite.png");

	Player player(&playerTexture, sf::Vector2u(4, 8), 0.2f, 50.0f);
	
	/*sf::Texture platformTexture1;
	platformTexture1.loadFromFile("Satoshi.png");*/

	Platform leftWindow(nullptr, sf::Vector2f(100.0f, 1080.0f), sf::Vector2f(-50.0f, 540.0f));
	Platform rightWindow(nullptr, sf::Vector2f(100.0f, 1080.0f), sf::Vector2f(1130.0f, 540.0f));
	Platform topWindow(nullptr, sf::Vector2f(1080.0f, 100.0f), sf::Vector2f(540.0f, -50.0f));
	Platform bottomWindow(nullptr, sf::Vector2f(1080.0f, 100.0f), sf::Vector2f(540.0f, 770.0f));
	

	//Platform platform2(nullptr, sf::Vector2f(100.0f, 1080.0f), sf::Vector2f(-50.0f, 540.0f));
	
	float deltaTime = 0.0f;
	sf::Clock clock;
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

	
		//Check Collision 0.0-push , 1.0-not push
		Collider playerCollision = player.GetCollider();
		leftWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
		rightWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
		topWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
		bottomWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
		
		
		player.Update(deltaTime);
		std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;

		window.clear();	
		player.Draw(window);
		leftWindow.Draw(window);
		rightWindow.Draw(window);
		topWindow.Draw(window);
		bottomWindow.Draw(window);
		//platform2.Draw(window);
		
		window.display();
		
	}

	return 0;
}