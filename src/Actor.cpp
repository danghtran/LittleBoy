#include <Actor.h>

Actor::~Actor()
{
}


Player::~Player()
{
}

void Player::move(int delX, int delY)
{
	renderRect->y += delY;
	renderRect->x += delX;
}
