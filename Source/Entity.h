#pragma once

#include<SDL2/SDL.h>

#include"Sprite.h"

class Entity
{
private:
	Sprite* eSprite;
	SDL_Rect eRect;
	SDL_Point rotAxis;
	SDL_RendererFlip flip;
	float ex;
	float ey;
	float er;
	float sx;
	float sy;
	static SDL_Point rotAxisBuffer;
public:
	Entity(Sprite* sprite, float x, float y);
	Entity();
	void move(float x, float y);
	void setPosition(float x, float y);
	float getX() { return ex; }
	float getY() { return ey; }
	void rotate(float r);
	void setRotation(float r);
	float getRotation() { return er; }
	void scale(float x, float y);
	float getScaleX() { return sx; }
	float getScaleY() { return sy; }
	void setFlip(bool h, bool v);
	Sprite* getSprite() { return eSprite; }
	SDL_Rect* getRect() { return &eRect; }
	SDL_Point* getRotationAxis() { return &rotAxis; }
	SDL_RendererFlip getFlip() { return flip; }
	int getWidth() { return eRect.w; }
	int getHeight() { return eRect.h; }
	static SDL_Point* getRotationAxisBuffer() { return &rotAxisBuffer; }
};

