#include "UIComponent.h"

#include<cmath>

UIComponent::UIComponent(SDL_Texture* texture, int x, int y)
{
	cTexture = texture;
	cx = x;
	cy = y;
	sx = 1;
	sy = 1;
	cRect = new SDL_Rect();
	cRect->x = cx;
	cRect->y = cy;
	SDL_QueryTexture(cTexture, NULL, NULL, &cRect->w, &cRect->h);
}

void UIComponent::move(int x, int y)
{
	cx += x;
	cy += y;
	cRect->x = cx;
	cRect->y = cy;
}

void UIComponent::setPosition(int x, int y)
{
	cx = x;
	cy = y;
	cRect->x = cx;
	cRect->y = cy;
}

void UIComponent::setScale(float x, float y)
{
	sx = x;
	sy = y;
	SDL_QueryTexture(cTexture, NULL, NULL, &cRect->w, &cRect->h);
	cRect->w *= (int)std::round(sx);
	cRect->h *= (int)std::round(sy);
}