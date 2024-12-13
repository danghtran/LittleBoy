#include <Sprite.h>

SpriteRegister::SpriteRegister()
{
}

SpriteRegister::~SpriteRegister()
{
	freeSprites();
}

SpriteRegister* SpriteRegister::instance;

SpriteRegister* SpriteRegister::getInstance()
{
	if (instance == NULL)
	{
		instance = new SpriteRegister();
	}
	return instance;
}

void SpriteRegister::clearInstance()
{
	if (instance != NULL)
	{
		instance->freeSprites();
		instance = NULL;
	}
}

SpriteSheet* SpriteRegister::getSpriteSheet(std::string path)
{
	return registeredSprite[path];
}

void SpriteRegister::freeSprites()
{
	// free alocated sprites
	std::map<string, SpriteSheet*>::iterator iter = registeredSprite.begin();
	while (iter != registeredSprite.end())
	{
		iter->second->free();
		++iter;
	}
	// clear all registered sprite tile
	registeredSprite.clear();
}

void SpriteRegister::initSprite(std::string path, std::list<SDL_Rect> rects)
{
	SpriteSheet* spriteSheet = new SpriteSheet();
	spriteSheet->load(path, rects);
	registeredSprite[path] = spriteSheet;
}

SpriteSheet::SpriteSheet()
{
	spriteTexture = NULL;
}

SpriteSheet::~SpriteSheet()
{
	free();
}

void SpriteSheet::load(std::string path, std::list<SDL_Rect> rects) {
	ViewRenderer* viewRenderer = ViewRenderer::getInstance();
	spriteTexture = viewRenderer->loadTexture(path);

	// Split texture into sprites
	for each (SDL_Rect rect in rects)
	{
		SDL_Rect* sprite = new SDL_Rect();
		sprite->x = rect.x;
		sprite->y = rect.y;
		sprite->w = rect.w;
		sprite->h = rect.h;
		sprites.push_back(sprite);
	}
}

void SpriteSheet::free()
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

SDL_Texture* SpriteSheet::getTexture()
{
	return spriteTexture;
}

SDL_Rect* SpriteSheet::getRandomSprite()
{
	return getSpriteAt(rand() % sprites.size());
}

SDL_Rect* SpriteSheet::getSpriteAt(int pos)
{
	return sprites.at(pos);
}
