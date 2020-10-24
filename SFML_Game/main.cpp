#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include <sstream>
#include <SFML/Audio.hpp>
void showEndGame();

int main()
{
	float windowWidth = 1170.0f, windowHigh = 800.0f;
	int countDie = 0;
	
	//Count State//
	int state = 1;
	
	//Render Window//
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHigh), "Ice Wall Walk", sf::Style::Close | sf::Style::Resize);
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
	sf::RectangleShape background(sf::Vector2f(windowWidth, windowHigh));
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
	lblStage.setPosition({ 0,0 });
	lblStage.setFont(font);
	lblStage.setString(showStage.str());

	int f2sec = 0, f1min = 0, f2min = 0;
	sf::Time elapsed = clock2.getElapsedTime();
	std::ostringstream showTime;
	showTime << f2min << f1min << ":" << f2sec << (int)elapsed.asSeconds() << ":" << elapsed.asMilliseconds() % 1000 / 10;
	sf::Text lblTime;
	lblTime.setCharacterSize(30);
	lblTime.setPosition({ 100, 0 });
	lblTime.setFont(font);
	lblTime.setString(showTime.str());

	//Collision Window windowWidth = 1170, windowHigh = 800//
	float frameWidthLeft = 100.0f, frameHighLeft = windowHigh;
	float frameWidthTop = windowWidth, frameHighTop = 100.0f;
	Platform leftWindow(nullptr, sf::Vector2f(frameWidthLeft, frameHighLeft), sf::Vector2f(-frameWidthLeft /2, frameHighLeft/2));
	Platform rightWindow(nullptr, sf::Vector2f(frameWidthLeft, frameHighLeft), sf::Vector2f(frameWidthTop + frameWidthLeft/2, frameHighLeft/2));
	Platform topWindow(nullptr, sf::Vector2f(frameWidthTop, frameHighTop), sf::Vector2f(frameWidthTop / 2, -frameHighTop / 2));
	Platform bottomWindow(nullptr, sf::Vector2f(frameWidthTop, frameHighTop), sf::Vector2f(frameWidthTop / 2, frameHighLeft + frameHighTop /2));
	 
	if (state == 1) //state 1//
	{
		int statusBox4 = 0, statusBox5 = 0, statusBox6 = 0;

		//Exit Way
		sf::RectangleShape exitWay(sf::Vector2f(380.0f, 350.0f));
		exitWay.setPosition(sf::Vector2f(700.0f, 100.0f));
		
		//Platform Box//
		Platform Box1(nullptr, sf::Vector2f(610.0f, 600.0f), sf::Vector2f(395.0f, 400.0f));
		Platform Box2(nullptr, sf::Vector2f(290.0f, 250.0f), sf::Vector2f(935.0f, 225.0f));
		Platform Box3(nullptr, sf::Vector2f(380.0f, 250.0f), sf::Vector2f(890.0f, 575.0f));
		Platform Box4(nullptr, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(835.0f, 50.0f));
		Platform Box5(&demonTexture, sf::Vector2f(100.0f, 90.0f), sf::Vector2f(1125.0f, 50.0f));
		Platform Box6(nullptr, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(1035.0f, 750.0f));
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
			Box3.GetCollider().CheckCollision(playerCollision, 1.0f);
			Box6.GetCollider().CheckCollision(playerCollision, 1.0f);

			//Draw in Window//
			player.Update(deltaTime);
			std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
			window.clear();
			window.draw(exitWay);
			/*window.draw(background);*/
			player.Draw(window);

			//Draw Window Collision//
			leftWindow.Draw(window);
			rightWindow.Draw(window);
			topWindow.Draw(window);
			bottomWindow.Draw(window);

			//Draw Box//
			Box1.Draw(window);
			Box2.Draw(window);
			Box3.Draw(window);
			if (player.GetPosition().x >= 925.0f &&  player.GetPosition().y <= 70.0f)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
						statusBox4 = 1;
				}
			}
			if (statusBox4)
			{
				Box4.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box4.Draw(window);
			}
			if (player.GetPosition().x >= 930.0f && player.GetPosition().y <= 70.0f)
			{
				statusBox5 = 1;
			}
			if (statusBox5)
			{
				Box5.Draw(window);
			}
			if (player.GetPosition().x >= 930.0f && player.GetPosition().y >= 740.0f && player.GetPosition().y <= 770.0f)
			{
				statusBox6 = 1;
			}
			if (statusBox6)
			{
				Box6.Draw(window);
			}
			if (player.GetPosition().x >= 944.0f && player.GetPosition().x <= 1000.0f && player.GetPosition().y == 750.0f)
			{
				std::cout << "Hello\n";
				exitWay.setFillColor(sf::Color::Black);
			}
			else
			{
				exitWay.setFillColor(sf::Color::White);
			}
			
			//Die
			if (player.GetPosition().x >= 1100 && player.GetPosition().y <= 70)
			{
				countDie += 1;
				sDie.play();
				player.SetPosition(45, 50);
			}

			//Draw Time
			window.draw(lblTime);
			window.draw(lblStage);

			//Go state 2
			if (player.GetPosition().x >= 1120 && player.GetPosition().y >= 745 && player.GetPosition().y <= 750)
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
		//Render Window//
		windowWidth = 1149;
		windowHigh = 1107;
	
		//BackGround//D
		backgroundTexture.loadFromFile("PokamonMap1.png");
		background.setTexture(&backgroundTexture);

		//In Game//
		while (window.isOpen())
		{
			//deltaTime//
			deltaTime = clock.restart().asSeconds();

			//Platform Box//
			Platform Box1(nullptr, sf::Vector2f(610.0f, 600.0f), sf::Vector2f(395.0f, 400.0f));
			Platform Box2(nullptr, sf::Vector2f(290.0f, 250.0f), sf::Vector2f(935.0f, 225.0f));
			Platform Box3(nullptr, sf::Vector2f(380.0f, 250.0f), sf::Vector2f(890.0f, 575.0f));
			Platform Box4(nullptr, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(835.0f, 50.0f));
			Platform Box5(&demonTexture, sf::Vector2f(100.0f, 90.0f), sf::Vector2f(1125.0f, 50.0f));
			Platform Box6(nullptr, sf::Vector2f(90.0f, 100.0f), sf::Vector2f(1035.0f, 750.0f));

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
			/*leftWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			rightWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			topWindow.GetCollider().CheckCollision(playerCollision, 1.0f);
			bottomWindow.GetCollider().CheckCollision(playerCollision, 1.0f);*/

			//Draw in Window//
			player.Update(deltaTime);
			std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
			window.clear(sf::Color(150, 150, 150));
			window.draw(background);
			player.Draw(window);

			//Draw Platform//
			/*leftWindow.Draw(window);
			rightWindow.Draw(window);
			topWindow.Draw(window);
			bottomWindow.Draw(window);*/

			//Draw Time//
			window.draw(lblTime);

			//Window display//
			window.display();
		}
	}

	

	return 0;
}


void showEndGame()
{
	sf::Font font;
	font.loadFromFile("LayijiMahaniyomV105.ttf");
	std::ostringstream showStage;
	showStage << "Stage 1";
	sf::Text lblStage;
	lblStage.setCharacterSize(30);
	lblStage.setPosition({ 0,0 });
	lblStage.setFont(font);
	lblStage.setString(showStage.str());
}