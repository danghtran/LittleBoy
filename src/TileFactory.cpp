#include <TileFactory.h>
#include <stdio.h>

TileFactory::TileFactory()
{
}

TileFactory::~TileFactory()
{
	freeSprites();
}

TileFactory* TileFactory::instance;

TileFactory* TileFactory::getInstance()
{
	if (instance == NULL)
	{
		instance = new TileFactory();
	}
	return instance;
}

void TileFactory::clearInstance()
{
	if (instance != NULL)
	{
		instance->freeSprites();
		instance = NULL;
	}
}

TileSprite* TileFactory::getSprite(std::string path)
{
	if (registeredSprite[path] == NULL) {
		TileSprite* tileSprite = new TileSprite();
		tileSprite->load(path);
		registeredSprite[path] = tileSprite;
	}
	return registeredSprite[path];
}

void TileFactory::freeSprites()
{
	// free alocated sprites
	std::map<string, TileSprite*>::iterator iter = registeredSprite.begin();
	while (iter != registeredSprite.end())
	{
		iter->second->free();
		++iter;
	}
	// clear all registered sprite tile
	registeredSprite.clear();
}

TileSprite::TileSprite()
{
	spriteTexture = NULL;
}

TileSprite::~TileSprite()
{
	free();
}

void TileSprite::load(std::string path) {
	ViewRenderer* viewRenderer = ViewRenderer::getInstance();
	spriteTexture = viewRenderer->loadTexture(path);

	int width = 0;
	int height = 0;
	SDL_QueryTexture(spriteTexture, NULL, NULL, &width, &height);
	
	// Split texture into sprites
	int mWidth = 0;
	int mHeight = 0;
	while (mHeight < height)
	{
		while (mWidth < width)
		{
			SDL_Rect* sprite = new SDL_Rect();
			sprite->x = mWidth;
			sprite->y = mHeight;
			sprite->w = 50;
			sprite->h = 50;
			sprites.push_back(sprite);

			mWidth += 50;
		}
		mHeight += 50;
		mWidth = 0;
	}
}

void TileSprite::free()
{
	if (spriteTexture != NULL)
	{
		SDL_DestroyTexture(spriteTexture);
		spriteTexture = NULL;
		for (int i = 0; i < sprites.size(); i++)
		{
			delete sprites.at(i);
		}
		sprites.clear();
	}
}

SDL_Texture* TileSprite::getSprite()
{
	return spriteTexture;
}

SDL_Rect* TileSprite::getRandomSprite()
{
	return sprites.at(rand() % sprites.size());
}
