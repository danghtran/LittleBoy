#include <Drawable.h>

MovableObject::~MovableObject()
{
}

PhysicObject::~PhysicObject()
{
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
