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

class PhysicObject: public Drawable
{
public:
	PhysicObject(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : Drawable(texture, sprite, render) {};
	virtual ~PhysicObject();
	virtual bool isPassable() = 0;
	virtual void scroll(int delta);
private:

};

class MovableObject: public PhysicObject
{
public:
	MovableObject(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : PhysicObject(texture, sprite, render) {};
	virtual ~MovableObject();
	virtual bool isPassable() = 0;
	virtual void move(int dir) = 0;
	void setSpeed(int val);
protected:
	int speed = 1;
};