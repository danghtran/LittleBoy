#pragma once
#include <ViewRenderer.h>;

class Drawable
{
private:
	SDL_Texture* texture;
	int height;
	int width;
public:
	virtual void draw();
};

class Tile : public Drawable
{
public:
	virtual bool isPassable();
	virtual bool isStretch();
};

class Obstacle : public Tile
{
	
};

//class MapTile : public Tile
//{
//private:
	//Obstacle* obstacle;
//};