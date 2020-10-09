#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "main.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Ice Wall Walk", sf::Style::Close | sf::Style::Resize);
	sf::Texture playerTexture;
	
	playerTexture.loadFromFile("FinSprite.png");
	Player player(&playerTexture, sf::Vector2u(4, 8), 0.2f, 50.0f);
	
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


		player.Update(deltaTime);
		
		//std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;

		window.clear();	
		player.Draw(window);
		window.display();
	}

	return 0;
}