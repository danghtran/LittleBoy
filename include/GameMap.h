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
	MapTile(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : Drawable(texture, sprite, render) { obstacle = NULL;};
	~MapTile();

	void scroll(int delta);
	void setObstacle(SDL_Texture* texture, SDL_Rect* sprite);
	void draw(ViewRenderer* viewRenderer) override;
	bool movable();
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

class MapLine: public BaseMap<MapTile>
{
protected:
	int y;
public:
	MapLine(int yAxis, SpriteSheet* spriteSheet);
	~MapLine();

	int getY();
	int getPreviousLineY();
	bool isOutOfScreen(int max);
	bool isPassedScreenTop();
	bool movable(int x);
	void scroll(int delta);
	void init();
	void render(ViewRenderer* viewRenderer);
	virtual void generateObstacles(int num, SpriteSheet* obstacleSheet) = 0;
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
	bool movable(int x, int y);
};

class StaticObstacle : public PhysicObject
{
public:
	StaticObstacle(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : PhysicObject(texture, sprite, render) {};
	~StaticObstacle();
	bool isPassable();
};

class MovingObstacle: public MovableObject
{
public:
	MovingObstacle(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : MovableObject(texture, sprite, render) {};
	~MovingObstacle();
	bool isPassable();
	void move(int dir);
};

class GrassLine : public MapLine
{
public:
	GrassLine(int yAxis, SpriteSheet* spriteSheet) : MapLine(yAxis, spriteSheet) {};
	~GrassLine();
	void generateObstacles(int num, SpriteSheet* obstacleSheet) override;
};

class RoadLine : public MapLine
{
private:
	std::list<MovableObject*> obstacles;
public:
	RoadLine(int yAxis, SpriteSheet* spriteSheet) : MapLine(yAxis, spriteSheet) {};
	~RoadLine();
	void generateObstacles(int num, SpriteSheet* obstacleSheet) override;
	void scroll(int delta) override;
	void render(ViewRenderer* viewRenderer) override;
};

class WaterLine : public MapLine
{
private:
	std::list<MovableObject*> obstacles;
public:
	WaterLine(int yAxis, SpriteSheet* spriteSheet) : MapLine(yAxis, spriteSheet) {};
	~WaterLine();
	void generateObstacles(int num, SpriteSheet* obstacleSheet) override;
	void scroll(int delta) override;
	void render(ViewRenderer* viewRenderer) override;
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
