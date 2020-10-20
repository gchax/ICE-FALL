#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"


//static const float VIEW_HEIGHT = 512.0f;
//
//void ResizeView(const sf::RenderWindow& window, sf::View& view)
//{
//	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
//	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
//}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Ice Wall Walk", sf::Style::Close | sf::Style::Resize);
	//sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	sf::Texture playerTexture;
	playerTexture.loadFromFile("FinSprite.png");

	Player player(&playerTexture, sf::Vector2u(4, 8), 0.2f, 50.0f);
	
	/*sf::Texture platformTexture1;
	platformTexture1.loadFromFile("Satoshi.png");*/

	Platform platform1(nullptr, sf::Vector2f(200.0f, 100.0f), sf::Vector2f(50.0f, 100.0f));
	Platform platform2(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(500.0f, 400.0f));
	
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

				case sf::Event::Resized:
					//ResizeView(window, view);
					break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

	
		
		Collider playerCollision = player.GetCollider();
		platform1.GetCollider().CheckCollision(playerCollision, 0.0f);
		platform2.GetCollider().CheckCollision(playerCollision, 1.0f);
		
		
		/*platform1.GetCollider().CheckCollision(platform1.GetCollider(), 0.0f);
		platform2.GetCollider().CheckCollision(platform2.GetCollider(), 1.0f);*/
		
		player.Update(deltaTime);
		std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
		//view.setCenter(player.GetPosition());

		window.clear();	
		//window.setView(view);
		player.Draw(window);
		platform1.Draw(window);
		platform2.Draw(window);
		
		window.display();
		
	}

	return 0;
}