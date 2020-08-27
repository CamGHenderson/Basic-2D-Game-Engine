#include "Tile.h"

#include<cmath>

Tile::Tile(SDL_Texture* texture, float x, float y)
{
	tTexture = texture;
	tx = x;
	ty = y;
	sx = 1;
	sy = 1;
	tRect = new SDL_Rect();
	tRect->x = (int)std::round(tx);
	tRect->y = (int)std::round(ty);
	SDL_QueryTexture(tTexture, NULL, NULL, &tRect->w, &tRect->h);
}

void Tile::move(float x, float y)
{
	tx += x;
	ty += y;
	tRect->x = (int)std::round(tx);
	tRect->y = (int)std::round(ty);
}

void Tile::scale(float x, float y)
{
	sx *= x;
	sy *= y;
	SDL_QueryTexture(tTexture, NULL, NULL, &tRect->w, &tRect->h);
	tRect->w *= (int)std::round(sx);
	tRect->h *= (int)std::round(sy);
}
