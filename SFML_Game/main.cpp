#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Ice Wall Walk", sf::Style::Close | sf::Style::Resize);
	
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Satoshi.png");


	Player player(&playerTexture, sf::Vector2u(3, 3), 0.3f, 50.0f);

	float deltaTime = 0.0f;
	sf::Clock clock;

	
	/*
	sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 3;
	textureSize.y /= 3;
	player.setTextureRect(sf::IntRect(textureSize.x*1,textureSize.y*2, textureSize.x, textureSize.y));
	*/
	
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					//ResizeView(window, view);
					break;
				}

		}

		//KeyBoard Input
		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			player.move(0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player.move(0.0f, 0.1f);
		}
		*/

		player.Update(deltaTime);
		

		window.clear();
		
		player.Draw(window);
		window.display();
	}

	return 0;
}