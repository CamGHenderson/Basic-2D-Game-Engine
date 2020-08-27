#include "KeyInput.h"

KeyInput::KeyInput()
{
	keyboardState = NULL;
}

void KeyInput::update()
{
	keyboardState = SDL_GetKeyboardState(NULL);
}

bool KeyInput::getKeyDown(SDL_Scancode scanCode)
{
	return keyboardState[scanCode];
}
