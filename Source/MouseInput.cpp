#include "MouseInput.h"

MouseInput::MouseInput()
{
	mx = 0;
	my = 0;
	lmb = false;
	rmb = false;
}

void MouseInput::update()
{
	SDL_GetMouseState(&mx, &my);
	SDL_PumpEvents();
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		lmb = true;
	else
		lmb = false;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		rmb = true;
	else
		rmb = false;
}