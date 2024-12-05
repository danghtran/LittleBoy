#include <GameMap.h>

MapTile::MapTile(int xAxis, int yAxis, SDL_Rect* sprite)
{
	x = xAxis;
	y = yAxis;
	spriteBox = sprite;
}

MapTile::~MapTile()
{
	spriteBox = NULL;
}

SDL_Rect* MapTile::getSpriteBox()
{
	return spriteBox;
}

int MapTile::getX()
{
	return x;
}

int MapTile::getY()
{
	return y;
}

void MapTile::scroll(int delta)
{
	y += delta;
}

MapLine::MapLine(int yAxis, TileSprite* spriteSheet)
{
	y = yAxis;
	spriteTexture = spriteSheet->getSprite();
	for (int i = 0; i < 12; i++)
	{
		MapTile* tile = new MapTile(i * 50, yAxis, spriteSheet->getRandomSprite());
		tiles.push_back(tile);
	}
}

MapLine::~MapLine()
{
	spriteTexture = NULL;
	for each (MapTile* tile in tiles)
	{
		delete tile;
	}
	tiles.clear();
}

std::list<MapTile*> MapLine::getTiles()
{
	return tiles;
}

SDL_Texture* MapLine::getSpriteTexture()
{
	return spriteTexture;
}

int MapLine::getPreviousLineY()
{
	return y - 50;
}

void MapLine::scroll(int delta)
{
	y += delta;
	for each (MapTile* tile in tiles)
	{
		tile->scroll(delta);
	}
}

bool MapLine::isOutOfScreen(int max)
{
	return y >= max;
}

bool MapLine::isAtScreenTop()
{
	return y == 0;
}

MapLine* GameMap::createLineAt(int y)
{
	TileFactory* tileFactory = TileFactory::getInstance();
	TileSprite* tileSprite;
	switch (rand() % 7)
	{
	case 1:
		tileSprite = tileFactory->getSprite("res/river.png");
		break;
	case 2:
		tileSprite = tileFactory->getSprite("res/street.png");
		break;
	default:
		tileSprite = tileFactory->getSprite("res/grassb.png");
		break;
	}
	return new MapLine(y, tileSprite);
}

GameMap::GameMap(int w, int h)
{
	width = w;
	height = h;
}

GameMap::~GameMap()
{
	clear();
}

void GameMap::init()
{
	ViewRenderer* viewRenderer = ViewRenderer::getInstance();
	for (int i = 0; i < 12; i++)
	{
		MapLine* mapLine = createLineAt(i * 50);
		viewRenderer->renderLine(mapLine);
		lines.push_back(mapLine);
	}
	viewRenderer->commitChange();
}

void GameMap::scroll(int delta)
{
	ViewRenderer* viewRenderer = ViewRenderer::getInstance();
	for each (MapLine* line in lines)
	{
		line->scroll(delta);
		viewRenderer->renderLine(line);
	}
	if (lines.back()->isOutOfScreen(height)) 
	{
		delete lines.back();
		lines.pop_back();
	}
	if (!lines.front()->isAtScreenTop()) 
	{
		MapLine* newLine = createLineAt(lines.front()->getPreviousLineY());
		lines.push_front(newLine);
		viewRenderer->renderLine(newLine);
	}
	viewRenderer->commitChange();
}

void GameMap::clear()
{
	for each (MapLine* line in lines)
	{
		delete line;
	}
	lines.clear();
}
