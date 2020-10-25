#include "Game.h"
#include "stdafx.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800,600), "Game 4", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new PlayerSprite();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if(this->ev.type ==sf::Event::KeyPressed && this-> ev.key.code == sf::Keyboard::Escape)
			this->window.close();
	}

	this->updatePlayer();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear(sf::Color::Green);

	//Render game
	this->renderPlayer();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this -> window;
}
