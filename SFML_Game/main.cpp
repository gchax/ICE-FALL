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
#include <vector>
#include "Bitmap.h"
#include "Restart.h"

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}



int main()
{
	// Window Height Weight 
	float  windowWidth = VIEW_HEIGHT, windowHight = VIEW_HEIGHT;

	// Render Window 
	sf::RenderWindow window(sf::VideoMode(int(windowWidth), int(windowHight)), "Satoshi Pajonpai", sf::Style::Close| sf::Style::Resize);
	window.setFramerateLimit(120);

	// View 
	sf::View view(sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT), sf::Vector2f(windowWidth, windowHight));

	// Player 
	sf::Texture playerTexture;
	playerTexture.loadFromFile("PerfectSprite.png");
	Player player(&playerTexture, sf::Vector2u(4, 8), 0.5f, 100.0f);

	// Texture Docter
	sf::Texture docterTexture;
	docterTexture.loadFromFile("Docter.png");

	// Pokeball Texture 
	sf::Texture pokeballTexture;
	pokeballTexture.loadFromFile("Pokeball4.png");

	// Die Texture 
	sf::Texture dieTexture;
	dieTexture.loadFromFile("die.png");

	// Black Texture 
	sf::Texture BlackTexture;
	BlackTexture.loadFromFile("Black.jpg");

	// Chest Texture 
	sf::Texture chestTexture;
	chestTexture.loadFromFile("chest.png");

	// Clock 
	float deltaTime = 0.0f;
	sf::Clock clock;

	// Font 
	sf::Font font;
	if (!font.loadFromFile("LayijiMahaniyomV105.ttf"))
		std::cout << "ERROR FONT";

	// Font GameOver 
	sf::Text textGameOver;
	textGameOver.setFont(font);
	textGameOver.setCharacterSize(256);
	textGameOver.setFillColor(sf::Color::Red);
	textGameOver.setStyle(sf::Text::Style::Bold);
	textGameOver.setString("Game Over");

	// Font Pokeball Bomb 
	sf::Text textPokeball;
	textPokeball.setFont(font);
	textPokeball.setCharacterSize(64);
	textPokeball.setFillColor(sf::Color::Red);
	textPokeball.setStyle(sf::Text::Style::Bold);
	textPokeball.setString("Pokeball is a Bomb!?");

	// Font Flower Prison 
	sf::Text textFloawer;
	textFloawer.setFont(font);
	textFloawer.setCharacterSize(64);
	textFloawer.setFillColor(sf::Color::Red);
	textFloawer.setStyle(sf::Text::Style::Bold);
	textFloawer.setString("Flowers have Venom");

	// Texture Text
	sf::Texture textFindKey;
	textFindKey.loadFromFile("text1.png");

	sf::Texture textDoNotGoSecoundFloor;
	textDoNotGoSecoundFloor.loadFromFile("text2.png");

	sf::Texture textHouse3_2;
	textHouse3_2.loadFromFile("textHouse3_2.png");

	sf::Texture textDoceter1;
	textDoceter1.loadFromFile("textDocter.png");

	// Manu State    
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
			
			case sf::Event::Resized:
				std::cout << "\Resized\n";
				ResizeView(window, view);
				break;
			}

		}
		window.clear();
		menu.draw(window);
		window.display();
		if (checkGameOpen == true)
			break;
	}
	 
	// Restart State    
	Restart restart(windowWidth, windowHight);
	sf::Texture pickachuMeme;
	pickachuMeme.loadFromFile("PickachuMeme.png");
	Platform pickachuBox(&pickachuMeme, sf::Vector2f(240, 240), sf::Vector2f(windowWidth/2 + 150, windowHight/2 - 50));
	
	// State obj 
	int state = 1;
	int countDie = 0;
	bool checkGameRestart = false;
	bool restartGame = false;

	// Run Game
	while (1)
	{	
		// status state
		
		// state
		if (state == 1) 
		{
			//Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("Map1.png");
			Platform Background1(&backgroundState5Texture, sf::Vector2f(224 * 64 / 16, 256 * 64 / 16), sf::Vector2f(224 * 64 / 32, 256 * 64 / 32));

			//BitMap Init
			std::vector<Bitmap> block0;
			int outdoor[16][14] = {
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 },
			};

			//DrawBitMap
			for (int mapX = 0; mapX < 14; mapX++)
			{
				for (int mapY = 0; mapY < 16; mapY++)
				{
					if (outdoor[mapY][mapX] == 1)
					{
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64) + 32, ((mapY) * 64) + 32), sf::Vector2f(64.f, 64.f));
						block0.push_back(outdoor);
					}
				}
			}
			
			//Platform Init
			Platform door(nullptr, sf::Vector2f(34.f, 2.f), sf::Vector2f(113.f * 64 / 16, 255.f * 64 / 16));
			Platform die(&dieTexture, sf::Vector2f(58.f * 2, 94.f * 1.5), sf::Vector2f((16 * 7) * 4 - 23, 16 * 11 * 4));

			//Run Game
			player.SetPosition(426, 427);
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
						std::cout << "\Resized\n";
						ResizeView(window, view);
						break;
					}
				}

				//Player Update
				player.Update(deltaTime);

				//BitMap Collision
				Collider playerCollision = player.GetCollider();
				for (int i = 0; i < block0.size(); i++)
					block0[i].getCollider().CheckCollision(playerCollision, 1.0f);
				
				//Window Collision
				if (player.GetPosition().x < 0 + 29)
				{
					player.SetPosition(29, player.GetPosition().y);
				}
				if (player.GetPosition().y < 0 + 47)
				{
					player.SetPosition(player.GetPosition().x, 47);
				}
				if (player.GetPosition().x + 29 > 224 * 64 / 16)
				{
					player.SetPosition(224 * 64 / 16 - 29, player.GetPosition().y);
				}
				if (player.GetPosition().y + 47 > 256 * 64 / 16)
				{
					player.SetPosition(player.GetPosition().x, 256 * 64 / 16 - 47);
				}

				//Draw
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				window.clear();
				Background1.Draw(window);
				player.Draw(window);
				window.setView(view);

				//Die
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					if (player.GetPosition().x >= (16 * 6) * 4 && player.GetPosition().x <= (16 * 7) * 4 && player.GetPosition().y >= (16 * 10) * 4 && player.GetPosition().y <= (16 * 11) * 4)
					{
						std::cout << "\nDIE\n";
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
								case sf::Event::Resized:
									std::cout << "\Resized\n";
									ResizeView(window, view);
									break;
								case sf::Event::KeyReleased:
									if (evnt.key.code == sf::Keyboard::Return)
										restartGame = true;
									break;
								}
							}

							if (restartGame)
							{
								std::cout << "xxxx\n\n";
								break;
							}
							window.clear();
							Background1.Draw(window);
							die.Draw(window);
							window.setView(view);

							window.display();
						}
					}
				}				
				//Goto State 2
				if (player.GetGlobalBounds().intersects(door.GetGlobalBounds()))
				{
					std::cout << "Goto State 2";
					state = 2;
					break;
				}
				//Goto Restart
				if (restartGame)
				{
					std::cout << "\nRestart in State 1\n";
					break;
				}
					
				//WIndow Display
				window.display();
			}
		}
		else if (state == 2)
		{
				//Set Position
				player.SetPosition(576,751);
				
				//Background
				sf::Texture backgroundState5Texture;
				backgroundState5Texture.loadFromFile("Map2.png");
				Platform Background2(&backgroundState5Texture, sf::Vector2f(576 * 64 / 16, 529 * 64 / 16), sf::Vector2f(576 * 64 / 32, 529 * 64 / 32));

				//BitMap Init
				std::vector<Bitmap> block0;
				int outdoor[33][36] = {
										{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
										{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
										{0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
										{0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
										{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
										{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
										{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
										{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
										{0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
										{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
										{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
				};

				//DrawBitMap
				for (int mapX = 0; mapX < 36; mapX++)
				{
					for (int mapY = 0; mapY < 33; mapY++)
					{
						if (outdoor[mapY][mapX] == 1)
						{
							Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 64) + 32, ((mapY) * 64) + 32), sf::Vector2f(64.f, 64.f));
							block0.push_back(outdoor);
						}
					}
				}

				//Run Game
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
							std::cout << "\Resized\n";
							ResizeView(window, view);
							break;
						}
					}

					//Player Update
					player.Update(deltaTime);
					
					// Window Collision
					if (player.GetPosition().x < 0 + 29 )
					{
						player.SetPosition(29, player.GetPosition().y);
					}
					if (player.GetPosition().y + 46 > 529 * 64 / 16)
					{
						player.SetPosition(player.GetPosition().x, 529 * 64 / 16 - 46);
					}

					//BitMap Collision
					Collider playerCollision = player.GetCollider();
					for (int i = 0; i < block0.size(); i++)
						block0[i].getCollider().CheckCollision(playerCollision, 1.0f);

					//Draw
					view.setCenter(player.GetPosition());
					std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
					window.clear();
					Background2.Draw(window);
					player.Draw(window);
					window.setView(view);



					window.display();
				}
		}
		else if (state == 5)
		{
			//Background
			sf::Texture backgroundState5Texture;
			backgroundState5Texture.loadFromFile("state5.png");
			Platform Box1(&backgroundState5Texture,  sf::Vector2f(768 * 90 / 16, 704 * 90 / 16), sf::Vector2f(768 * 90 / 32, 704 * 90 / 32) );
			std::vector<Bitmap> block0;
			int outdoor[44][48] = { 
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			};
			
			//DrawMap
			for (int mapX = 0; mapX < 48; mapX++)
			{
				for (int mapY = 0; mapY < 44; mapY++)
				{
					if (outdoor[mapY][mapX] == 1)
					{
						Bitmap outdoor(nullptr, sf::Vector2f(((mapX) * 90) + 45, ((mapY) * 90) + 45), sf::Vector2f(90.f, 90.f));
						block0.push_back(outdoor);
					}
				}
			}
			
			//Run Game
			player.SetPosition(1300, 3290);
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
						std::cout << "\Resized\n";
						ResizeView(window, view);
						break;
					}
				}

				//Collider
				Collider playerCollision = player.GetCollider();
				for (int i = 0; i < block0.size(); i++) 
					block0[i].getCollider().CheckCollision(playerCollision, 1.0f);

				//Draw
				player.Update(deltaTime);
				view.setCenter(player.GetPosition());
				std::cout << "x = " << player.GetPosition().x << " y = " << player.GetPosition().y << std::endl;
				
				window.clear();
				Box1.Draw(window);
				player.Draw(window);
				
				window.setView(view);
				window.display();
			}
		}

		// restart
		if (restartGame)
		{
			// Count Die
			countDie += 1;
		
			//set View
			view.setCenter(windowWidth / 1.5, windowHight / 2);
			std::cout << "Restart";

			//Render
			while (window.isOpen())
			{		
				//selected ITEM
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::KeyReleased:
						switch (evnt.key.code) {
						case sf::Keyboard::W:
							restart.MoveUp();
							break;
						case sf::Keyboard::S:
							restart.MoveDown();
							break;
						case sf::Keyboard::Return:
							switch (restart.GetPressedItem()) {
							case 0:
								std::cout << "Restart is Pressed" << std::endl;
								state = 1;
								checkGameRestart = true;
								break;
							case 1:
								std::cout << "manu is Pressed" << std::endl;
								break;
							}
						}
						break;

					case sf::Event::Closed:
						window.close();
						break;
					
					case sf::Event::Resized:
						std::cout << "\Resized\n";
						ResizeView(window, view);
						break;
					}

				}
		
				//Draw Restart Menu
				window.clear();
				restart.draw(window);
				pickachuBox.Draw(window);
				window.setView(view);
				window.display();

				//Reset Status
				if (checkGameRestart == true)
				{
					checkGameRestart = false;
					restartGame = false;
					break;
				}
					
			}
		}
	}
	
	return 0;
}