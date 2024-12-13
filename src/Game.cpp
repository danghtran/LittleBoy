#include <Game.h>

Game::Game()
{
	map = new GameMap(600, 600);
	map->init();
	//initPlayer();
}

void Game::clear()
{
	delete map;
	delete player;
}

void Game::render(ViewRenderer* viewRenderer)
{
	map->render(viewRenderer);
	//player->draw(viewRenderer);
	viewRenderer->commitChange();
}

void Game::initPlayer()
{
	SpriteRegister* factory = SpriteRegister::getInstance();
	//factory->initSprite("res/boy.png", 60, 60);

	SpriteSheet* sprite = factory->getSpriteSheet("res/boy.png");
	SDL_Rect* render = new SDL_Rect();
	render->x = 300;
	render->y = 550;
	render->w = 60;
	render->h = 60;
	player = new Player(sprite->getTexture(), sprite->getRandomSprite(), render);
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


