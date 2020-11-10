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

static const float VIEW_HEIGHT = 900.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}



int main()
{
	////////// Endgame status //////////
	int pokeball = 0;
	int flower = 0;

	////////// window Height Weight //////////
	float  windowWidth = VIEW_HEIGHT, windowHight = VIEW_HEIGHT;

	////////// State Count //////////
	int state = 5;

	////////// Render Window //////////
	sf::RenderWindow window(sf::VideoMode(int(windowWidth), int(windowHight)), "Satoshi Pajonpai", sf::Style::Close| sf::Style::Resize);
	window.setFramerateLimit(120);

	////////// View //////////
	sf::View view(sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT), sf::Vector2f(windowWidth, windowHight));

	////////// Player //////////
	sf::Texture playerTexture;
	playerTexture.loadFromFile("PerfectSprite.png");
	Player player(&playerTexture, sf::Vector2u(4, 8), 0.5f, 50.0f);

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
						state = 5;
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

	//////////    Restart State    //////////
	Restart restart(windowWidth, windowHight);
	
	////////// state obj //////////
	bool check_state2 = false;
	bool checkGameRestart = false;
	bool restartGame = false;

	////////// Run Game //////////
	while (1)
	{	
		//status state
		bool boxstate2_1 = false;
		
		//state
		if (state == 5)
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

		//restart
		if (restartGame)
		{
			/*player.SetPosition(windowWidth, windowHight);*/
			
			std::cout << "Restart";
			while (window.isOpen())
			{
				//set View
				view.setCenter(windowWidth / 1.5, windowHight / 2);
				window.setView(view);
				
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
					}

				}
				

				window.clear();
				restart.draw(window);
				window.display();
				if (checkGameRestart == true)
				{
					checkGameRestart = false;
					check_state2 = false;
					pokeball = 0;
					flower = 0;
					break;
				}
					
			}
		}

		/*
		//if (pokeball == 1)
		//{
		//	while (window.isOpen())
		//	{
		//		textGameOver.setPosition(player.GetPosition().x - 450, player.GetPosition().y - 300);
		//		textPokeball.setPosition(player.GetPosition().x - 225, player.GetPosition().y);

		//		//Text Display
		//		window.clear();
		//		window.draw(textGameOver);
		//		window.draw(textPokeball);
		//		window.display();

		//		//CloseGame 1
		//		sf::Event evnt;
		//		while (window.pollEvent(evnt))
		//		{
		//			switch (evnt.type)
		//			{
		//			case sf::Event::Closed:
		//			window.close();
		//				break;
		//			}
		//		}

		//		//CloseGame 2
		//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		//		{
		//			window.close();
		//		}
		//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		//		{
		//			player.SetPosition(667.f, 460.f);
		//			check_state2 = false;
		//			pokeball = 0;
		//			state = 1;
		//			break;
		//		}
		//	}
		//}
		//if (flower == 1)
		//{
		//	while (window.isOpen())
		//	{
		//		textGameOver.setPosition(player.GetPosition().x - 450, player.GetPosition().y - 300);
		//		textFloawer.setPosition(player.GetPosition().x - 225, player.GetPosition().y);
		//		//Text Display
		//		window.clear();
		//		window.draw(textGameOver);
		//		window.draw(textFloawer);
		//		window.display();

		//		//CloseGame 1
		//		sf::Event evnt;
		//		while (window.pollEvent(evnt))
		//		{
		//			switch (evnt.type)
		//			{
		//			case sf::Event::Closed:
		//				window.close();
		//				break;
		//			}
		//		}
		//		//CloseGame 2
		//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		//		{
		//			window.close();
		//		}
		//	}
		//}		
		*/ //Pokeball 
		
	}
	
	return 0;
}