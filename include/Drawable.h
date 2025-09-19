#pragma once
#include <SDL.h>
#include <ViewRenderer.h>

class Drawable
{
protected:
	SDL_Texture* texture;
	SDL_Rect* spriteRect;
	SDL_Rect* renderRect;
public:
	Drawable(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) :
		texture(texture), spriteRect(sprite), renderRect(render) {}
	virtual ~Drawable();
	void draw();
	virtual void draw(ViewRenderer* viewRenderer);
	int getX();
	int getY();
};

class Scrollable : public Drawable
{
public:
	Scrollable(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : Drawable(texture, sprite, render) {};
	virtual ~Scrollable() {};
	virtual void scroll(int delta);
};

class PhysicObject: public Scrollable
{
protected:
	bool passable = true;
	bool collidable = false;
public:
	PhysicObject(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render, bool isPassable, bool isCollidable) : Scrollable(texture, sprite, render) 
	{
		passable = isPassable; 
		collidable = isCollidable;
	};
	~PhysicObject();
	bool isCollided(int x);
	bool isPassable();
	bool isCollidable();
};

class MovableObject: public PhysicObject
{
public:
	MovableObject(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render, bool isPassable, bool isCollidable) : PhysicObject(texture, sprite, render, isPassable, isCollidable) {};
	~MovableObject();
	virtual void move(int delX, int delY);
	void setSpeed(int val);
protected:
	int speed = 1;
};

class DraggableObject: public MovableObject
{
public:
	DraggableObject(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : MovableObject(texture, sprite, render, true, false) {};
	~DraggableObject();
protected:
	MovableObject* obj = NULL;
};