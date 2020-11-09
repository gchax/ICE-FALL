#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include <sstream>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
#include "Menu.h"

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(1200*aspectRatio, 950);
}

int main()
{
	////////// Endgame status //////////
	int pokeball = 0;
	int flower = 0;

	////////// window Height Weight //////////
	float  windowWidth = 1200.0f, windowHight = 950.0f;

	////////// State Count //////////
	int state = 1;

	////////// Render Window //////////
	sf::RenderWindow window(sf::VideoMode(int(windowWidth), int(windowHight)), "Satoshi Pajonpai", sf::Style::Close);
	window.setFramerateLimit(120);

	////////// View //////////
	sf::View view(sf::Vector2f(667.f, 460.f), sf::Vector2f(windowWidth, windowHight));

	////////// Player //////////
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Satoshi.png");
	Player player(&playerTexture, sf::Vector2u(4, 8), 0.2f, 50.0f);

	sf::Texture docterTexture;
	docterTexture.loadFromFile("Docter.png");
	

	////////// Pokeball Texture //////////
	sf::Texture pokeballTexture;
	pokeballTexture.loadFromFile("Pokeball4.png");

	////////// Black Texture //////////
	sf::Texture BlackTexture;
	BlackTexture.loadFromFile("Black.jpg");

	////////// Chest Texture //////////
	sf::Texture chestTexture;
	chestTexture.loadFromFile("chest.png");

	////////// Clock //////////
	float deltaTime = 0.0f;
	sf::Clock clock;

	////////// Font //////////
	sf::Font font;
	if (!font.loadFromFile("LayijiMahaniyomV105.ttf"))
		std::cout << "ERROR FONT";

	////////// Font GameOver //////////
	sf::Text textGameOver;
	textGameOver.setFont(font);
	textGameOver.setCharacterSize(256);
	textGameOver.setFillColor(sf::Color::Red);
	textGameOver.setStyle(sf::Text::Style::Bold);
	textGameOver.setString("Game Over");

	////////// Font Pokeball Bomb //////////
	sf::Text textPokeball;
	textPokeball.setFont(font);
	textPokeball.setCharacterSize(64);
	textPokeball.setFillColor(sf::Color::Red);
	textPokeball.setStyle(sf::Text::Style::Bold);
	textPokeball.setString("Pokeball is a Bomb!?");

	////////// Font Flower Prison //////////
	sf::Text textFloawer;
	textFloawer.setFont(font);
	textFloawer.setCharacterSize(64);
	textFloawer.setFillColor(sf::Color::Red);
	textFloawer.setStyle(sf::Text::Style::Bold);
	textFloawer.setString("Flowers have Venom");

	//PlatForm Text1
	sf::Texture textFindKey;
	textFindKey.loadFromFile("text1.png");

	sf::Texture textDoNotGoSecoundFloor;
	textDoNotGoSecoundFloor.loadFromFile("text2.png");

	sf::Texture textHouse3_2;
	textHouse3_2.loadFromFile("textHouse3_2.png");

	sf::Texture textDoceter1;
	textDoceter1.loadFromFile("textDocter.png");


	////////// state obj //////////
	bool check_state2 = false;
	
	//////////    Manu State    //////////
	Menu menu(windowWidth, windowHight);
	bool checkGameOpen = false;
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::KeyReleased:
				switch (evnt.key.code) {
				case sf::Keyboard::W:
					menu.MoveUp();
					break;
				case sf::Keyboard::S:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem()) {
					case 0:
						std::cout << "Play is Pressed";
						state = 1;
						checkGameOpen = true;
						break;
					case 1:
						std::cout << "Leaderboard is Pressed";
						break;
					case 2:
						window.close();
						break;
					}
				}
				break;

			case sf::Event::Closed:
				window.close();
				break;
			}

		}
		window.clear();
		menu.draw(window);

		window.display();
		if (checkGameOpen == true)
			break;
	}

	////////// Run Game //////////
	while (1)
	{
		bool boxstate2_1 = false;
		if (state == 1)
		{
			//Spawn Point
			if (check_state2)
				player.SetPosition(845.f, 693.f);
			else
				player.SetPosition(667.f, 460.f);

			//BackGround//
			float backGroundWidth = windowWidth / 2.0f;
			float backGroundHeight = windowHight / 2.0f;
			sf::RectangleShape background(sf::Vector2f(880, 715));
			sf::Texture backgroundTexture;
			backgroundTexture.loadFromFile("StarterRoom.png");
			background.setTexture(&backgroundTexture);
			background.setOrigin(background.getSize() / 2.0f);
			background.setPosition(sf::Vector2f(backGroundWidth, backGroundHeight));

			//Platform Furniture//
			Platform Box1(&BlackTexture, sf::Vector2f(342.0f, 150.0f), sf::Vector2f(171.0f + 160.0f, 138.0f + 117.5f - 20.0f));
			Platform Box2(&BlackTexture, sf::Vector2f(204.0f, 136.0f), sf::Vector2f(458.5f + 160.0f, 70.0f + 117.5f - 20.0f));
			Platform Box3(&BlackTexture, sf::Vector2f(57.0f, 139.0f), sf::Vector2f(595.5f + 160.0f, 158.0f + 117.5f - 50.0f));
			Platform Box8(nullptr, sf::Vector2f(200.0f, 131.0f), sf::Vector2f(843.5f, 155.5f + 117.5f - 50.0f));
			Platform Box4(&BlackTexture, sf::Vector2f(132.0f, 131.0f), sf::Vector2f(814.5f + 160.0f, 155.5f + 117.5f - 50.0f));
			Platform Box5(&BlackTexture, sf::Vector2f(200.0f, 132.0f), sf::Vector2f(278.0f + 160.0f, 372.0f + 117.5f));
			Platform Box6(&BlackTexture, sf::Vector2f(280.0f, 110.0f), sf::Vector2f(300.0f + 160.0f + 16.f, 558.5f + 117.5f));
			
			//Platform pokeball//
			Platform Box7(&pokeballTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(684.6f + 160.0f, 220.7f + 117.5f + 250.0f));

			//Platform Floor 2//
			Platform Stair(&BlackTexture, sf::Vector2f(20, 20), sf::Vector2f(685.0f + 160.0f, 175.f + 117.5f));

		
			

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
					case sf::Event::Resized:
						//ResizeView(window, view);
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
				Box8.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box4.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box5.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box6.GetCollider().CheckCollision(playerCollision, 1.0f);

				//Draw
				player.Update(deltaTime);
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;

				window.clear();
				window.setView(view);
			
				window.draw(background);
				//Box1.Draw(window);
				//Box2.Draw(window);
				//Box3.Draw(window);
				//Box4.Draw(window);
				//Box5.Draw(window);
				//Box6.Draw(window);
				//Box8.Draw(window);
				//Stair.Draw(window);
				Box7.Draw(window);
				player.Draw(window);

				//Text Find Key
				if (player.GetGlobalBounds().intersects(Stair.GetGlobalBounds()))
				{
					Platform Text1(&textFindKey, sf::Vector2f(1180, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					Text1.Draw(window);
				}
				//Game Over Pokeball
				if (player.GetPosition().x > 805.0f && player.GetPosition().x <= 872.0f && player.GetPosition().y >= 620.0f - 100.f && player.GetPosition().y <= 690.0f - 100.f)
				{
					pokeball = 1;
					break;
				}

				//Goto state 2
				if (player.GetPosition().x > 824.0f && player.GetPosition().x <= 938.0f && player.GetPosition().y >= 787.0f && player.GetPosition().y <= 788.0f)
				{
					check_state2 = true;
					//spawn point
					player.SetPosition(315.f, 433.f);
					std::cout << "state 2\n";
					state = 2;
					break;
				}

				window.display();
			}

		}
		else if (state == 2)
		{
			check_state2 = true;

			//BackGround//
			float backGroundWidth = windowWidth / 2.0f;
			float backGroundHeight = windowHight / 2.0f;
			sf::RectangleShape background(sf::Vector2f(1528, 1428));
			sf::Texture backgroundTexture;
			backgroundTexture.loadFromFile("PokamonMap1.png");
			background.setTexture(&backgroundTexture);
			background.setOrigin(background.getSize() / 2.0f);
			background.setPosition(sf::Vector2f(backGroundWidth, backGroundHeight));

			//Platform Tree//
			Platform Box1(&BlackTexture, sf::Vector2f(96.0f, 1428.f), sf::Vector2f(-47.5f - 50.f, 535.5f));
			Platform Box2(&BlackTexture, sf::Vector2f(98.0f, 210.f), sf::Vector2f(-22.f + 50.0f, -39.5f - 50.0f));
			Platform Box3(&BlackTexture, sf::Vector2f(384.0f + 125.f, 104.f), sf::Vector2f(215 + 100.0f, -91.5f - 100.0f));
			Platform Box4(&BlackTexture, sf::Vector2f(96.0f, 1428.f), sf::Vector2f(-47.5f - 50.f + 1400, 535.5f));
			Platform Box5(&BlackTexture, sf::Vector2f(98.0f, 210.f), sf::Vector2f(-22.f + 50.0f + 1150, -39.5f - 50.0f));
			Platform Box6(&BlackTexture, sf::Vector2f(384.0f + 125.f, 104.f), sf::Vector2f(215 + 500.0f + 300, -91.5f - 100.0f));
			Platform Box7(&BlackTexture, sf::Vector2f(98.0f, 210.f), sf::Vector2f(-22.f + 50.0f - 25, -39.5f - 50.0f + 1120));
			Platform Box8(&BlackTexture, sf::Vector2f(98.0f, 210.f), sf::Vector2f(-22.f + 50.0f + 1150, -39.5f - 50.0f + 980));
			Platform Box9(&BlackTexture, sf::Vector2f(98.0f, 210.f), sf::Vector2f(-22.f + 50.0f + 1150 - 130, -39.5f - 50.0f + 1100));
			Platform Box10(&BlackTexture, sf::Vector2f(1528.f, 120.f), sf::Vector2f(764.f, 1428.f - 310.f));

			//Platform House//
			Platform House1_1(nullptr, sf::Vector2f(256.f, 173.f), sf::Vector2f(412.f - 164.0f, 375.5f - 144.f - 100.f));
			Platform House1_2(nullptr, sf::Vector2f(306, 210), sf::Vector2f(414.f - 164.0f, 467.5f - 144.f - 100.f));
			Platform House1_3(nullptr, sf::Vector2f(40, 30), sf::Vector2f(440.f, 315.f));
			Platform House2_1(nullptr, sf::Vector2f(256.f, 173.f), sf::Vector2f(412.f - 164.0f + 706.f, 375.5f - 144.f - 100.f));
			Platform House2_2(nullptr, sf::Vector2f(306, 210), sf::Vector2f(414.f - 164.0f + 708.f, 467.5f - 144.f - 100.f));
			Platform House2_3(nullptr, sf::Vector2f(40, 30), sf::Vector2f(440.f + 320.f, 315.f));
			Platform House3_1(nullptr, sf::Vector2f(348 + 100, 285 - 5), sf::Vector2f(545.f - 164.f, 947.f - 144.f - 100));
			Platform House3_2(nullptr, sf::Vector2f(50, 50), sf::Vector2f(540.5f - 164.f, 1146.f - 144.f - 100));
			Platform House3_3(nullptr, sf::Vector2f(50, 30), sf::Vector2f(1120.f - 164.f, 883.5f - 144.f - 100.f));

			//Platform Flower//
			Platform Flower1(nullptr, sf::Vector2f(57, 44), sf::Vector2f(349.5f - 164.f, 709.0f - 144.f - 100.f));
			Platform Flower2(nullptr, sf::Vector2f(57, 44), sf::Vector2f(155.5f - 164.f, 500.0f - 144.f - 20.f));

			//Platform Grass//
			Platform Grass1(nullptr, sf::Vector2f(100, 150), sf::Vector2f(-164 + 197.5 - 50 , -239+ 406.5 - 100));

			//Platform Chest//
			Platform Chest1(&chestTexture, sf::Vector2f(60, 60), sf::Vector2f(-164 + 148.0, -239 + 310.0));

			//Platform pokeball//
			Platform pokeball2_1(&pokeballTexture, sf::Vector2f(40.0f, 40.0f), sf::Vector2f(-164 + 220.5, -239 + 579.0));

			//Platform goto state 4
			Platform door2_3(nullptr, sf::Vector2f(15, 15), sf::Vector2f(-164 + 604.5, -239 + 1075));

			//In Game
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

				//Cheek Collision Tree
				Collider playerCollision = player.GetCollider();
				Box1.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box2.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box3.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box4.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box5.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box6.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box7.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box8.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box9.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box10.GetCollider().CheckCollision(playerCollision, 1.0f);
				
				//Check Collision House
				House1_1.GetCollider().CheckCollision(playerCollision, 1.0f);
				House1_2.GetCollider().CheckCollision(playerCollision, 1.0f);
				House1_3.GetCollider().CheckCollision(playerCollision, 1.0f);
				House2_1.GetCollider().CheckCollision(playerCollision, 1.0f);
				House2_2.GetCollider().CheckCollision(playerCollision, 1.0f);
				House2_3.GetCollider().CheckCollision(playerCollision, 1.0f);
				House3_1.GetCollider().CheckCollision(playerCollision, 1.0f);
				House3_2.GetCollider().CheckCollision(playerCollision, 1.0f);
				House3_3.GetCollider().CheckCollision(playerCollision, 1.0f);

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
				Box7.Draw(window);
				Box8.Draw(window);
				Box9.Draw(window);
				Box10.Draw(window);
				House1_1.Draw(window);
				House1_2.Draw(window);
				House1_3.Draw(window);
				House2_1.Draw(window);
				House2_2.Draw(window);
				House2_3.Draw(window);
				House3_1.Draw(window);
				House3_2.Draw(window);
				House3_3.Draw(window);
				Flower1.Draw(window);
				Flower2.Draw(window);
				

				window.draw(background);
				
				door2_3.Draw(window);
				
				//text House 3
				Platform boxChecktextHouse3_2(nullptr, sf::Vector2f(55, 55), sf::Vector2f(540.5f - 164.f, 1146.f - 144.f - 100));
				if (player.GetGlobalBounds().intersects(boxChecktextHouse3_2.GetGlobalBounds()))
				{
					Platform Text1(&textHouse3_2, sf::Vector2f(1180, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					Text1.Draw(window);
				}

				//chest
				if (player.GetGlobalBounds().intersects(Grass1.GetGlobalBounds()))
					boxstate2_1 = true;
				if (boxstate2_1)
					pokeball2_1.Draw(window);
				else
					Chest1.Draw(window);

				//Game Over flower
				if (player.GetPosition().x >= 155.0f && player.GetPosition().x <= 215.0f && player.GetPosition().y >= 414.0f && player.GetPosition().y <= 445.0f)
				{
					flower = 1;
					break;
				}
				if (player.GetPosition().x >= -37 && player.GetPosition().x <= 20 && player.GetPosition().y >= 314.0f && player.GetPosition().y <= 365)
				{
					flower = 1;
					break;
				}

				//Goto state 1 (starter room)
				if (player.GetPosition().x >= 300.0f && player.GetPosition().x <= 319.0f && player.GetPosition().y >= 377.8f && player.GetPosition().y <= 381.0f)
				{
					check_state2 = true;
					player.SetPosition(845.f, 693.f);
					state = 1;
					break;
				}

				//Goto state 3 (Haruka room)
				if (player.GetPosition().x >= 860.0f && player.GetPosition().x <= 900.0f && player.GetPosition().y >= 377.8f && player.GetPosition().y <= 381.0f)
				{
					check_state2 = true;
					player.SetPosition(845.f, 693.f);
					state = 3;
					break;
				}

				//Goto state 4 (Docktor room)
				if (player.GetGlobalBounds().intersects(door2_3.GetGlobalBounds()))
				{
					check_state2 = true;
					player.SetPosition(642.f, 840.f);
					state = 4;
					break;
				}

				player.Draw(window);
				window.display();
			}

		}
		else if (state == 3)
		{
			//spawn point
			player.SetPosition(359.f, 699.f);

			//BackGround//
			sf::Texture backgroundTexture;
			backgroundTexture.loadFromFile("state3.png");
			float backGroundWidth = windowWidth / 2.0f;
			float backGroundHeight = windowHight / 2.0f;
			sf::RectangleShape background(sf::Vector2f(870, 700));
			background.setTexture(&backgroundTexture);
			background.setOrigin(background.getSize() / 2.0f);
			background.setPosition(sf::Vector2f(backGroundWidth, backGroundHeight));

			//In Game
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

				//Platform Furniture//
				Platform Box1(&BlackTexture, sf::Vector2f(116.0f, 146.0f), sf::Vector2f(165 + 580 + 15, 125 + 142 - 60));
				Platform Box2(&BlackTexture, sf::Vector2f(159.0f, 95.0f), sf::Vector2f(165 + 718.5, 125 + 178.5 - 70));
				Platform Box3(&BlackTexture, sf::Vector2f(220.0f, 50.0f), sf::Vector2f(165 + 559.5 + 40, 125 + 334 - 10));
				Platform Box4(&BlackTexture, sf::Vector2f(206.0f, 108.0f), sf::Vector2f(165 + 419.5, 125 + 54 - 30));
				Platform Box5(&BlackTexture, sf::Vector2f(45.0f, 222.0f), sf::Vector2f(165 + 279 + 5, 125 + 110 - 60));
				Platform Box6(&BlackTexture, sf::Vector2f(135.0f, 220.0f), sf::Vector2f(165 + 67.5,125 + 111.5 - 60));
				Platform Box7(&BlackTexture, sf::Vector2f(275.0f, 110.0f), sf::Vector2f(165 + 556,125 + 520.5));
				Platform Box8(&BlackTexture, sf::Vector2f(140.0f, 42.0f), sf::Vector2f(165 + 155,125 + 672 + 45));
				Platform Box9(&BlackTexture, sf::Vector2f(106.0f, 205.0f), sf::Vector2f(165 + 188, 125 + 120 - 60));
				Platform Box10(&BlackTexture, sf::Vector2f(106.0f, 205.0f), sf::Vector2f(165 + 188, 125 + 120 - 50));

				
				//Background Collision
				if (player.GetPosition().x < 165 + 45)
					player.SetPosition(165 + 45, player.GetPosition().y);
				if (player.GetPosition().x > 165 + 870 - 45)
					player.SetPosition(165 + 870 - 45, player.GetPosition().y);
				if (player.GetPosition().y < 125.5 + 45)
					player.SetPosition(player.GetPosition().x, 125 + 45);
				if (player.GetPosition().y > 125.5 + 700 - 45)
					player.SetPosition(player.GetPosition().x, 125 + 700 - 45);

				//Cheek Collision Furniture
				Collider playerCollision = player.GetCollider();
				Box1.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box2.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box3.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box4.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box5.GetCollider().CheckCollision(playerCollision, 1.0f);
				Box6.GetCollider().CheckCollision(playerCollision, 1.0f);			
				Box7.GetCollider().CheckCollision(playerCollision, 1.0f);			
				Box9.GetCollider().CheckCollision(playerCollision, 1.0f);			

				//Goto state 2
				if (player.GetGlobalBounds().intersects(Box8.GetGlobalBounds()))
				{
					player.SetPosition(888.5, 409.5);
					state = 2;
					break;
				}
				
				//Draw
				player.Update(deltaTime);
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				window.setView(view);
				//Box1.Draw(window);
				//Box2.Draw(window);
				//Box3.Draw(window);
				//Box4.Draw(window);
				//Box5.Draw(window);
				//Box6.Draw(window);
				//Box7.Draw(window);
				//Box9.Draw(window);
				window.draw(background);
				Box8.Draw(window);
				if (player.GetGlobalBounds().intersects(Box10.GetGlobalBounds()))
				{
					Platform Text1(&textDoNotGoSecoundFloor, sf::Vector2f(1180, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					Text1.Draw(window);
				}
				
				
				player.Draw(window);
				window.display();
			}
		}
		else if (state == 4)
		{
			//BackGround//
			sf::Texture backgroundTexture;
			backgroundTexture.loadFromFile("state4.png");
			float backGroundWidth = windowWidth / 2.0f;
			float backGroundHeight = windowHight / 2.0f;
			sf::RectangleShape background(sf::Vector2f(1030, 1015));
			background.setTexture(&backgroundTexture);
			background.setOrigin(background.getSize() / 2.0f);
			background.setPosition(sf::Vector2f(backGroundWidth, backGroundHeight));
		
			//Platform init//
			Platform Docter(&docterTexture, sf::Vector2f(60.f, 80.f), sf::Vector2f(85 + 552, -32.5 + 411));
			Platform checkDocter(&BlackTexture, sf::Vector2f(30, 50), sf::Vector2f(85 + 552, -32.5 + 411 - 10));

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

				//Background Collision
				if (player.GetPosition().x < 85 + 45)
					player.SetPosition(85 + 45, player.GetPosition().y);
				if (player.GetPosition().x > 85 + 1030 - 45)
					player.SetPosition(85 + 1030 - 45, player.GetPosition().y);
				if (player.GetPosition().y < -32.5 + 45)
					player.SetPosition(player.GetPosition().x, -32.5 + 45);
				if (player.GetPosition().y > -32.5 + 1015 - 45)
					player.SetPosition(player.GetPosition().x, -32.5 + 1015 - 45);

				//Cheek Collision Furniture
				Collider playerCollision = player.GetCollider();
				checkDocter.GetCollider().CheckCollision(playerCollision, 1.0f);

				//Draw
				player.Update(deltaTime);
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				window.setView(view);

				window.draw(background);
				checkDocter.Draw(window);
				Docter.Draw(window);
				player.Draw(window);
				
				if (player.GetGlobalBounds().intersects(Docter.GetGlobalBounds()))
				{
					Platform Text(&textDoceter1, sf::Vector2f(1180, 120), sf::Vector2f(player.GetPosition().x, player.GetPosition().y + 400));
					Text.Draw(window);
					std::cout << "X";
				}
				window.display();
			}
		}


		if (pokeball == 1)
		{
			while (window.isOpen())
			{
				textGameOver.setPosition(player.GetPosition().x - 450, player.GetPosition().y - 300);
				textPokeball.setPosition(player.GetPosition().x - 225, player.GetPosition().y);

				//Text Display
				window.clear();
				window.draw(textGameOver);
				window.draw(textPokeball);
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					player.SetPosition(667.f, 460.f);
					check_state2 = false;
					pokeball = 0;
					state = 1;
					break;
				}
			}
		}
		if (flower == 1)
		{
			while (window.isOpen())
			{
				textGameOver.setPosition(player.GetPosition().x - 450, player.GetPosition().y - 300);
				textFloawer.setPosition(player.GetPosition().x - 225, player.GetPosition().y);
				//Text Display
				window.clear();
				window.draw(textGameOver);
				window.draw(textFloawer);
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
		}		

		
	}
	
	return 0;
}