#pragma once
#include <TileFactory.h>
#include <list>

using namespace std;

template <class T>
class BaseMap
{
public:
	
protected:
	int width;
	int height;
};

class MapTile
{
public:
	MapTile(int xAxis, int yAxis, SDL_Rect* sprite);
	~MapTile();

	SDL_Rect* getSpriteBox();
	int getX();
	int getY();

	void scroll(int delta);

private:
	// For render quad
	int x;
	int y;
	// For sprite box
	SDL_Rect* spriteBox;
};

class MapLine
{
private:
	int y;
	SDL_Texture* spriteTexture;
	std::list<MapTile*> tiles;
public:
	MapLine(int yAxis, TileSprite* spriteSheet);
	~MapLine();

	std::list<MapTile*> getTiles();
	SDL_Texture* getSpriteTexture();
	int getPreviousLineY();

	void scroll(int delta);
	bool isOutOfScreen(int max);
	bool isAtScreenTop();
};

class GameMap
{
private:
	std::list<MapLine*> lines;
	int width;
	int height;
	MapLine* createLineAt(int y);
public:
	GameMap(int w, int h);
	~GameMap();
	void init();
	void scroll(int delta);
	void clear();
};


