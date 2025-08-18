#include <Game.h>

Game::Game()
{
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
	factory->initSprite("res/bear.png", 1, 1);

	SpriteSheet* sprite = factory->getSpriteSheet("res/bear.png");
	// Starting position
	SDL_Rect* render = new SDL_Rect();
	render->x = 300;
	render->y = 550;
	render->w = 50;
	render->h = 50;
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
			plPos--;
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
			plPos++;
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

void Game::loadTheme(Theme theme, std::string file)
{
	// register theme...
	ThemeRegister* themeRegister = ThemeRegister::getInstance();
	themeRegister->registerTile(GRASS, theme, "res/grassnb.png");
	themeRegister->registerTile(WATER, theme, "res/river.png");
	themeRegister->registerTile(ROAD, theme, "res/street.png");
	themeRegister->registerObstacle(GRASS, theme, "res/light.png");
	themeRegister->registerObstacle(ROAD, theme, "res/car.png");
	themeRegister->registerObstacle(WATER, theme, "res/water.png");
	SpriteRegister* spriteRegister = SpriteRegister::getInstance();

	spriteRegister->initSprite("res/grassnb.png", 2, 2);
	spriteRegister->initSprite("res/river.png", 1, 1);
	spriteRegister->initSprite("res/street.png", 1, 1);
	spriteRegister->initSprite("res/light.png", 2, 2);
	spriteRegister->initSprite("res/car.png", 1, 1);
	spriteRegister->initSprite("res/water.png", 1, 1);
}

void Game::reset()
{
	clear();
	init();
}

bool Game::checkCollision()
{
	return (*plPos)->checkCollision(player->getX());
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

void Game::init()
{
	map = new GameMap(600, 600);
	map->init();
	plPos = map->getInitialPlPos();
	initPlayer();
}


