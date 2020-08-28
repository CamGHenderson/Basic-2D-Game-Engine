#pragma once

#include<SDL2/SDL.h>

class Tile
{
private:
	SDL_Texture* tTexture;
	float tx, ty;
	float sx, sy;
	SDL_Rect* tRect;
public:
	Tile(SDL_Texture* texture, float x, float y);
	void move(float x, float y);
	void setPosition(float x, float y);
	float getX() { return tx; }
	float getY() { return ty; }
	void scale(float x, float y);
	float getScaleX() { return sx; }
	float getScaleY() { return sy; }
	SDL_Rect* getRect() { return tRect; }
	SDL_Texture* getTexture() { return tTexture; }
};

