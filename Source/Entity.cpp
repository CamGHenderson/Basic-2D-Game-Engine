#include "Entity.h"

#include<cmath>

SDL_Point Entity::rotAxisBuffer = SDL_Point();

Entity::Entity(Sprite* sprite, float x, float y)
{
	eSprite = sprite;
	ex = x;
	ey = y;
	eRect.x = (int)std::round(ex);
	eRect.y = (int)std::round(ey);
	eRect.w = sprite->getAnimation()->getFrame().w;
	eRect.h = sprite->getAnimation()->getFrame().h;
	rotAxis.x = eRect.w / 2;
	rotAxis.y = eRect.h / 2;
	er = 0;
	sx = 1;
	sy = 1;
	flip = SDL_FLIP_NONE;
}

Entity::Entity()
{
	eSprite = NULL;
	eRect = SDL_Rect();
	rotAxis = SDL_Point();
	ex = 0;
	ey = 0;
	er = 0;
	sx = 0;
	sy = 0;
	flip = SDL_FLIP_NONE;
}

void Entity::move(float x, float y)
{
	ex += x;
	ey += y;
	eRect.x = (int)std::round(ex);
	eRect.y = (int)std::round(ey);
}

void Entity::setPosition(float x, float y)
{
	ex = x;
	ey = y;
	eRect.x = (int)std::round(ex);
	eRect.y = (int)std::round(ey);
}

void Entity::rotate(float r)
{
	er += r;
}

void Entity::setRotation(float r)
{
	er = r;
}

void Entity::scale(float x, float y)
{
	sx *= x;
	sy *= y;
}

void Entity::setFlip(bool h, bool v)
{
	if (h & v)
		flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (h)
		flip = SDL_FLIP_HORIZONTAL;
	else if (v)
		flip = SDL_FLIP_VERTICAL;
	else
		flip = SDL_FLIP_NONE;
}
