#pragma once
#include <Sprite.h>
#include <Drawable.h>
#include <ViewRenderer.h>
#include <Theme.h>
#include <list>

using namespace std;

class MapTile: public Drawable
{
public:
	MapTile(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : Drawable(texture, sprite, render) { obstacle = NULL; };
	~MapTile();

	void scroll(int delta);
	void setObstacle(PhysicObject* physicObj);
private:
	PhysicObject* obstacle;
};

template <class T>
class BaseMap
{
public:
	void clear();
	virtual void init() = 0;
	virtual void scroll(int delta) = 0;
	virtual void render(ViewRenderer* viewRenderer) = 0;
	BaseMap();
	virtual ~BaseMap();
protected:
	std::list<T*> elements;
};

class MapLine: BaseMap<MapTile>
{
private:
	int y;
public:
	MapLine(int yAxis, SpriteSheet* spriteSheet);
	~MapLine();

	int getPreviousLineY();
	bool isOutOfScreen(int max);
	void generateObstacles();

	bool isPassedScreenTop();
	void scroll(int delta);
	void init();
	void render(ViewRenderer* viewRenderer);
	using BaseMap::clear;
};

class GameMap: BaseMap<MapLine>
{
private:

	int width;
	int height;
	Theme theme;
	MapLine* createLineAt(int y);
public:
	GameMap(int w, int h);
	~GameMap();
	void init();
	void scroll(int delta);
	void render(ViewRenderer* viewRenderer);
	using BaseMap::clear;
	void applyTheme(Theme theme);
};

/**
	FACTORY
**/

class TileFactory
{
public:
	TileFactory();
	virtual ~TileFactory();
	SpriteSheet* getObstacle(Theme theme);
	SpriteSheet* getTile(Theme theme);
	virtual MapLine* getLine(int y, Theme theme) = 0;
protected:
	virtual TileType getType() = 0;
	SpriteSheet* getSpriteSheetInternal(std::string path);
	std::string getObstaclePath(Theme theme);
	std::string getTilePath(Theme theme);
};

class GrassTileFactory : TileFactory
{
public:
	~GrassTileFactory();
	MapLine* getLine(int y, Theme theme) override;
	static TileFactory* getInstance();
protected:
	TileType getType() override;
private:
	GrassTileFactory();
	static GrassTileFactory* instance;
};

class WaterTileFactory : TileFactory
{
public:
	~WaterTileFactory();
	MapLine* getLine(int y, Theme theme) override;
	static TileFactory* getInstance();
protected:
	TileType getType() override;
private:
	WaterTileFactory();

	static WaterTileFactory* instance;
};

class RoadTileFactory : TileFactory
{
public:
	~RoadTileFactory();
	MapLine* getLine(int y, Theme theme) override;
	static TileFactory* getInstance();
protected:
	TileType getType() override;
private:
	RoadTileFactory();

	static RoadTileFactory* instance;
};
