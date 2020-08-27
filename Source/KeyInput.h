#pragma once

#include<SDL2/SDL.h>

class KeyInput
{
private:
	const Uint8* keyboardState;
public:
	KeyInput();
	void update();
	bool getKeyDown(SDL_Scancode scanCode);
};

