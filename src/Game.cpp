#include <Game.h>

Game::Game()
{
	map = new GameMap(600, 600);
	map->init();
}

void Game::clear()
{
	map->clear();
	delete map;
}

Game::~Game()
{
	clear();
}

void Game::update()
{
	// adjust speed
	int speed = 1;
	map->scroll(speed);
}


