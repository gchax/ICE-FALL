#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include <sstream>
#include <SFML/Audio.hpp>

int main()
{
	/*float windowWidth = 1080.0f, windowHigh = 720.0f;*/
	
	//Count State//
	int state = 1;
	
	//Render Window//
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Ice Wall Walk", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(120);

	//main music//
	sf::Music musicBackground;
	musicBackground.openFromFile("mainSong.ogg");
	musicBackground.setVolume(15.0);
	musicBackground.play();

	//skill music//
	sf::SoundBuffer soundDie;
	soundDie.loadFromFile("die.wav");
	sf::Sound sDie;
	sDie.setBuffer(soundDie);
	sDie.setVolume(30.0);

	//BackGround//
	sf::RectangleShape background(sf::Vector2f(1080, 720));
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Map1.jpg");
	background.setTexture(&backgroundTexture);

	//Player//
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Satoshi.png");
	Player player(&playerTexture, sf::Vector2u(4, 8), 0.2f, 50.0f);

	//Platform Texture//
	sf::Texture demonTexture;
	demonTexture.loadFromFile("GrimV3.png");
	sf::Texture wallTexture;
	wallTexture.loadFromFile("groundBackground.jpg");

	//Clock//
	float deltaTime = 0.0f;
	sf::Clock clock;

	//Time//
	sf::Clock clock2;
	sf::Font font;
	font.loadFromFile("LayijiMahaniyomV105.ttf");
	std::ostringstream showStage;
	showStage << "Stage 1";
	sf::Text lblStage;
	lblStage.setCharacterSize(30);
	lblStage.setPosition({ 10,720 });
	lblStage.setFont(font);
	lblStage.setString(showStage.str());

	int f2sec = 0, f1min = 0, f2min = 0;
	sf::Time elapsed = clock2.getElapsedTime();
	std::ostringstream showTime;
	showTime << f2min << f1min << ":" << f2sec << (int)elapsed.asSeconds() << ":" << elapsed.asMilliseconds() % 1000 / 10;
	sf::Text lblTime;
	lblTime.setCharacterSize(30);
	lblTime.setPosition({ 0,0 });
	lblTime.setFont(font);
	lblTime.setString(showTime.str());

	//Collision Window//
	Platform leftWindow(nullptr, sf::Vector2f(100.0f, 1080.0f), sf::Vector2f(-50.0f, 540.0f));
	Platform rightWindow(nullptr, sf::Vector2f(100.0f, 1080.0f), sf::Vector2f(1130.0f, 540.0f));
	Platform topWindow(nullptr, sf::Vector2f(1080.0f, 100.0f), sf::Vector2f(540.0f, -50.0f));
	Platform bottomWindow(nullptr, sf::Vector2f(1080.0f, 100.0f), sf::Vector2f(540.0f, 770.0f));

	if (state == 1) //state 1//
	{
		int statusBox4 = 0, statusBox5 = 0;

		//Collosion Block//
		Platform Box1(nullptr, sf::Vector2f(880.0f, 160.0f), sf::Vector2f(540.0f, 207.5f));
		Platform Box2(nullptr, sf::Vector2f(880.0f, 160.0f), sf::Vector2f(540.0f, 512.5f));
		Platform Box3(nullptr, sf::Vector2f(880.0f, 180.0f), sf::Vector2f(540.0f, 360.0f));
		Platform Box4(nullptr, sf::Vector2f(100.0f, 150.0f), sf::Vector2f(700.0f, 55.0f));
		Platform Box5(&demonTexture, sf::Vector2f(120.0f, 150.0f), sf::Vector2f(1030.0f, 55.0f));
		/*Box5.body.setFillColor(sf::Color(255, 255, 255, 0));*/

		//In Game
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

			//Time//
			sf::Time elapsed = clock2.getElapsedTime();
			showTime << f2min << f1min << ":" << f2sec << (int)elapsed.asSeconds() << ":" << elapsed.asMilliseconds() % 1000 / 10;
			if (elapsed.asSeconds() >= 10)
			{
				clock2.restart();
				f2sec += 1;
			}
			if (f2sec >= 6)
			{
				f1min += 1;
				f2sec = 0;
			}
			if (f2min >= 10)
			{
				f1min += 1;
				f2min = 0;
			}
			lblTime.setString(showTime.str());
			showTime.str("");

			//Exit Game//
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			//Check Collision (0.0-push , 1.0-not push)//
			Collider playerCollision = player.GetCollider();
			leftWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			rightWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			topWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			bottomWindow.GetCollider().CheckCollision(playerCollision, 1.0f);

			Box1.GetCollider().CheckCollision(playerCollision, 1.0f);
			Box2.GetCollider().CheckCollision(playerCollision, 1.0f);
			Box3.GetCollider().CheckCollision(playerCollision, 0.0f);


			//Trap in Game//
			if (player.GetPosition().x >= 1000 && player.GetPosition().y <= 80)
			{
				//Box4.body.setFillColor(sf::Color(255, 255, 255, 255));
				sDie.play();
				player.SetPosition(0.0f, 0.0f);
			}
			if (player.GetPosition().x >= 900 && player.GetPosition().y >= 500 && player.GetPosition().x <= 970)
			{
				sDie.play();
				player.SetPosition(0.0f, 0.0f);
			}


			//Draw in Window//
			player.Update(deltaTime);
			std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
			window.clear(sf::Color(150, 150, 150));
			window.draw(background);
			player.Draw(window);

			//Draw Platform//
			leftWindow.Draw(window);
			rightWindow.Draw(window);
			topWindow.Draw(window);
			bottomWindow.Draw(window);

			/*Box1 Box2 Box3*/
			Box1.Draw(window);
			Box2.Draw(window);
			Box3.Draw(window);
			/*Box4 Box 5*/
			if (player.GetPosition().x >= 850 && player.GetPosition().y <= 80)
			{
				statusBox5 = 1;
			}
			if (statusBox5 == 1)
			{
				Box5.Draw(window);

			}
			if (player.GetPosition().y <= 80)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					if (player.GetPosition().x >= 750 && player.GetPosition().x <= 800)
						statusBox4 = 2;
				}

			}
			if (statusBox4 == 2)
			{
				Box4.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box4.Draw(window);
			}
			
			window.draw(lblTime);

			//Go state 2
			if (player.GetPosition().x == 1030 && player.GetPosition().y == 665)
			{
				window.clear(sf::Color(150, 150, 150));
				player.SetPosition(0.0f, 0.0f);
				state = 2;
				break;
				
			}

			//Window display
			window.display();
		}
	}
	if (state == 2) //state 2//
	{
		//In Game//
		while (window.isOpen())
		{
			//deltaTime//
			deltaTime = clock.restart().asSeconds();

			//Time//
			sf::Time elapsed = clock2.getElapsedTime();
			showTime << f2min << f1min << ":" << f2sec << (int)elapsed.asSeconds() << ":" << elapsed.asMilliseconds() % 1000 / 10;
			if (elapsed.asSeconds() >= 10)
			{
				clock2.restart();
				f2sec += 1;
			}
			if (f2sec >= 6)
			{
				f1min += 1;
				f2sec = 0;
			}
			if (f2min >= 10)
			{
				f1min += 1;
				f2min = 0;
			}
			lblTime.setString(showTime.str());
			showTime.str("");

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

			//Exit Game//
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			//Check Collision (0.0-push , 1.0-not push)//
			Collider playerCollision = player.GetCollider();
			leftWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			rightWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			topWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			bottomWindow.GetCollider().CheckCollision(playerCollision, 1.0f);

			//Draw in Window//
			player.Update(deltaTime);
			std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
			window.clear(sf::Color(150, 150, 150));
			window.draw(background);
			player.Draw(window);

			//Draw Platform//
			leftWindow.Draw(window);
			rightWindow.Draw(window);
			topWindow.Draw(window);
			bottomWindow.Draw(window);

			//Draw Time//
			window.draw(lblTime);

			//Window display//
			window.display();
		}
	}

	

	return 0;
}