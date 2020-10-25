#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include <sstream>
#include <SFML/Audio.hpp>

int main()
{
	//window Height Weight
	float windowHight = 1100.0, windowWidth = 1170.0;

	//State Count//
	int state = 1;

	//Render Window//
	sf::RenderWindow window(sf::VideoMode(int(windowWidth), int(windowHight)), "Satoshi Pajonpai", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(120);

	//View
	sf::View view(sf::Vector2f(580.0f, 500.0f), sf::Vector2f(windowWidth, windowHight));

	//Player//
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Satoshi.png");
	Player player(&playerTexture, sf::Vector2u(4, 8), 0.2f, 50.0f);

	//Clock//
	float deltaTime = 0.0f;
	sf::Clock clock;

	if (state == 1)
	{
		//BackGround//
		float backGroundWidth = windowWidth / 2.0f;
		float backGroundHeight = windowHight / 2.0f;
		sf::RectangleShape background(sf::Vector2f(880, 715));
		sf::Texture backgroundTexture;
		backgroundTexture.loadFromFile("StarterRoom.png");
		background.setTexture(&backgroundTexture);
		background.setOrigin(background.getSize() / 2.0f);
		background.setPosition(sf::Vector2f(backGroundWidth, backGroundHeight));


		//Game Play//
		while (window.isOpen())
		{
			//deltaTime//
			deltaTime = clock.restart().asSeconds();

			//Close Window//
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

			if (player.GetPosition().x < 145 + 45)
				player.SetPosition(145 + 45, player.GetPosition().y);
			if (player.GetPosition().x > 145 + 880 - 45)
				player.SetPosition(145 + 880 - 45, player.GetPosition().y);
			if (player.GetPosition().y < 192.5 + 45)
				player.SetPosition(player.GetPosition().x, 192.5 + 45);
			if (player.GetPosition().y > 907.5 - 45)
				player.SetPosition(player.GetPosition().x, 907.5 - 45);

			//Draw
			player.Update(deltaTime);
			view.setCenter(player.GetPosition());
			std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;

			window.clear();
			window.setView(view);
			window.draw(background);
			player.Draw(window);

			window.display();
		}

	}

	return 0;
}