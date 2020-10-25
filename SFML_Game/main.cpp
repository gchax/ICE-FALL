#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include <sstream>
#include <SFML/Audio.hpp>
#include <time.h>
#include<windows.h>
int main()
{
	//window Height Weight
	float  windowWidth = 1200.0f, windowHight = 950.0f;

	//State Count//
	int state = 1;

	//Render Window//
	sf::RenderWindow window(sf::VideoMode(int(windowWidth), int(windowHight)), "Satoshi Pajonpai", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(120);

	//View
	sf::View view(sf::Vector2f(667.f, 460.f), sf::Vector2f(windowWidth, windowHight));

	//Player//
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Satoshi.png");
	Player player(&playerTexture, sf::Vector2u(4, 8), 0.2f, 50.0f);

	//Pokeball Texture//
	sf::Texture pokeball;
	pokeball.loadFromFile("Pokeball4.png");

	//Black Texture//
	sf::Texture BlackTexture;
	BlackTexture.loadFromFile("Black.jpg");


	//Clock//
	float deltaTime = 0.0f;
	sf::Clock clock;

	//Font//
	sf::Font font;
	if (!font.loadFromFile("LayijiMahaniyomV105.ttf"))
		std::cout << "ERROR FONT";
	sf::Text textGameOver;
	textGameOver.setFont(font);
	textGameOver.setCharacterSize(256);

	textGameOver.setFillColor(sf::Color::Red);
	textGameOver.setStyle(sf::Text::Style::Bold);
	textGameOver.setString("Game Over");

	if (state == 1)
	{
		//Platform Furniture//
		Platform Box1(&BlackTexture, sf::Vector2f(342.0f, 150.0f), sf::Vector2f(171.0f + 160.0f, 138.0f + 117.5f - 20.0f));
		Platform Box2(&BlackTexture, sf::Vector2f(204.0f, 136.0f), sf::Vector2f(458.5f + 160.0f, 70.0f + 117.5f - 20.0f));
		Platform Box3(&BlackTexture, sf::Vector2f(57.0f, 139.0f), sf::Vector2f(595.5f + 160.0f, 158.0f + 117.5f - 50.0f));
		Platform Box4(&BlackTexture, sf::Vector2f(132.0f, 131.0f), sf::Vector2f(814.5f + 160.0f, 155.5f + 117.5f - 50.0f));
		Platform Box5(&BlackTexture, sf::Vector2f(200.0f, 132.0f), sf::Vector2f(278.0f + 160.0f, 372.0f + 117.5f));
		Platform Box6(&BlackTexture, sf::Vector2f(311.0f, 100.0f), sf::Vector2f(332.0f + 160.0f, 558.5f + 117.5f));
		Platform Box7(&pokeball, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(684.6f + 160.0f, 220.7f + 117.5f + 350.0f));

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

			//Background Collision
			if (player.GetPosition().x < 160 + 45)
				player.SetPosition(160 + 45, player.GetPosition().y);
			if (player.GetPosition().x > 160 + 880 - 45)
				player.SetPosition(160 + 880 - 45, player.GetPosition().y);
			if (player.GetPosition().y < 117.5 + 45)
				player.SetPosition(player.GetPosition().x, 117.5 + 45);
			if (player.GetPosition().y > 117.5 + 715 - 45)
				player.SetPosition(player.GetPosition().x, 117.5 + 715 - 45);

			//Cheek Collision Furniture
			Collider playerCollision = player.GetCollider();
			Box1.GetCollider().CheckCollision(playerCollision, 1.0f);
			Box2.GetCollider().CheckCollision(playerCollision, 1.0f);
			Box3.GetCollider().CheckCollision(playerCollision, 1.0f);
			Box4.GetCollider().CheckCollision(playerCollision, 1.0f);
			Box5.GetCollider().CheckCollision(playerCollision, 1.0f);
			Box6.GetCollider().CheckCollision(playerCollision, 1.0f);

			//Draw
			player.Update(deltaTime);
			view.setCenter(player.GetPosition());
			std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;

			window.clear();
			window.setView(view);
			Box1.Draw(window);
			Box2.Draw(window);
			Box3.Draw(window);
			Box4.Draw(window);
			Box5.Draw(window);
			Box6.Draw(window);
			window.draw(background);
			Box7.Draw(window);
			player.Draw(window);

			//Game Over
			if (player.GetPosition().x > 805.0f && player.GetPosition().x <= 872.0f && player.GetPosition().y >= 620.0f && player.GetPosition().y <= 690.0f)
			{
				break;
			}

			//state 2
			if (player.GetPosition().x > 824.0f && player.GetPosition().x <= 938.0f && player.GetPosition().y >= 787.0f && player.GetPosition().y <= 788.0f)
			{
				std::cout << "state 2\n";
				state = 2;
				break;
			}

			window.display();
		}

	}
	if (state == 2)
	{
		//spawn point
		player.SetPosition(315.f, 369.f);

		//BackGround//
		float backGroundWidth = windowWidth / 2.0f;
		float backGroundHeight = windowHight / 2.0f;
		sf::RectangleShape background(sf::Vector2f(1528, 1428));
		sf::Texture backgroundTexture;
		backgroundTexture.loadFromFile("PokamonMap1.png");
		background.setTexture(&backgroundTexture);
		background.setOrigin(background.getSize() / 2.0f);
		background.setPosition(sf::Vector2f(backGroundWidth, backGroundHeight));
		while (window.isOpen())
		{
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


	//EndGame
	while (window.isOpen())
	{
		textGameOver.setPosition(player.GetPosition().x - 450, player.GetPosition().y - 200);
		//Text Display
		window.clear();
		window.draw(textGameOver);
		window.display();

		//CloseGame 1
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
		//CloseGame 2
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}


	return 0;
	
}