#include <Drawable.h>
#include <Sprite.h>

class Actor: public Drawable
{
public:
	Actor(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render): Drawable(texture, sprite, render) {};
	virtual ~Actor();

private:

};

class Player : public Actor
{
public:
	Player(SDL_Texture* texture, SDL_Rect* sprite, SDL_Rect* render) : Actor(texture, sprite, render) {};
	~Player();
private:

};

