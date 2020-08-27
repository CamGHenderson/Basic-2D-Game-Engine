#pragma once

#include<SDL2/SDL.h>

class UIComponent
{
private:
	SDL_Texture* cTexture;
	SDL_Rect* cRect;
	int cx, cy;
	float sx, sy;
public:
	UIComponent(SDL_Texture* texture, int x, int y);
	void move(int x, int y);
	void setPosition(int x, int y);
	int getX() { return cx; }
	int getY() { return cy; }
	void setScale(float x, float y);
	float getScaleX() { return sx; }
	float getScaleY() { return sy; }
	SDL_Texture* getTexture() { return cTexture; }
	SDL_Rect* getRect() { return cRect; }
};

