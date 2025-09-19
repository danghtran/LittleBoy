#include <Drawable.h>
#include <Sprite.h>

class Actor: public MovableObject
{
public:
	Actor(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render): MovableObject(texture, sprite, render, true, true) {};
	virtual ~Actor();
	
private:

};

class Player : public Actor
{
public:
	Player(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : Actor(texture, sprite, render) {};
	~Player();
	void move(int delX, int delY) override;
private:

};

