#include <Game.h>

Game::Game()
{
	map = new GameMap(600, 600);
	map->init();
	initPlayer();
}

void Game::clear()
{
	delete map;
	delete player;
}

void Game::render(ViewRenderer* viewRenderer)
{
	map->render(viewRenderer);
	player->draw(viewRenderer);
	viewRenderer->commitChange();
}

void Game::initPlayer()
{
	SpriteRegister* factory = SpriteRegister::getInstance();
	/* TODO: register character skins somewhere else */
	factory->initSprite("res/boy.png", 1, 1);

	SpriteSheet* sprite = factory->getSpriteSheet("res/boy.png");
	// Starting position
	SDL_Rect* render = new SDL_Rect();
	render->x = 300;
	render->y = 550;
	render->w = 60;
	render->h = 60;
	player = new Player(sprite->getTexture(), sprite->getRandomSprite(), render);
}

void Game::movePlayer(int dir)
{
	switch (dir)
	{
	case 0:
		if (map->movable(player->getX(), player->getY() - 50))
		{
			player->move(0, -50);
		}
		break;
	case 1:
		if (map->movable(player->getX() + 50, player->getY()))
		{
			player->move(50, 0);
		}
		break;
	case 2:
		if (map->movable(player->getX(), player->getY() + 50))
		{
			player->move(0, 50);
		}
		break;
	case 3:
		if (map->movable(player->getX() - 50, player->getY()))
		{
			player->move(-50, 0);
		}
		break;
	}
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
	player->move(0, speed);
}


