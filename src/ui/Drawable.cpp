#include <Drawable.h>

MovableObject::~MovableObject()
{
}

void MovableObject::setSpeed(int val)
{
	speed = val;
}

PhysicObject::~PhysicObject()
{
}

void Scrollable::scroll(int delta)
{
	this->renderRect->y += delta;
}

Drawable::~Drawable()
{
	texture = NULL;
	spriteRect = NULL;
	delete renderRect;
	renderRect = NULL;
}

void Drawable::draw()
{
	ViewRenderer* viewRenderer = ViewRenderer::getInstance();
	draw(viewRenderer);
}

void Drawable::draw(ViewRenderer* viewRenderer)
{
	if (viewRenderer == NULL)
	{
		viewRenderer = ViewRenderer::getInstance();
	}
	viewRenderer->renderSprite(texture, spriteRect, renderRect);
}

int Drawable::getX()
{
	return renderRect->x;
}

int Drawable::getY()
{
	return renderRect->y;
}

void MovableObject::move(int dir)
{
	this->renderRect->x += speed;
	if (renderRect->x > 600)
	{
		renderRect->x = -50;
	}
}

bool PhysicObject::isCollided(int x)
{
	if (renderRect->x <= x && renderRect->x + renderRect->w > x)
	{
		return true;
	}
	return false;
}

bool PhysicObject::isPassable()
{
	return passable;
}

bool PhysicObject::isCollidable()
{
	return collidable;
}
