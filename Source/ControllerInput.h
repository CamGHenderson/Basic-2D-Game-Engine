#pragma once
#include<SDL2/SDL.h>

class ControllerInput
{
private:
	const char* cExit;
	SDL_Joystick* cJoyStick;
	SDL_GameController* cController;
	int lStickX, lStickY;
	int rStickX, rStickY;
	bool lTrigger;
	bool rTrigger;
	bool buttons[15];
public:
	ControllerInput();
	void update(SDL_Event rEvent);
	void controllerUpdate();
	void destroy();
	int getLeftStickX() { return lStickX; }
	int getLeftStickY() { return lStickY; }
	int getRightStickX() { return rStickX; }
	int getRightStickY() { return rStickY; }
	bool getLeftTrigger() { return lTrigger; }
	bool getRightTrigger() { return rTrigger; }
	bool getButton(SDL_GameControllerButton button) { return buttons[(int)button]; }
};

