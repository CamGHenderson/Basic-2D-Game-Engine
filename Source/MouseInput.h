#pragma once

#include<SDL2/SDL.h>

class MouseInput
{
private:
	int mx, my;
	bool lmb, rmb;
public:
	MouseInput();
	void update();
	int getMouseX() { return mx; }
	int getMouseY() { return my; }
	bool getLMB() { return lmb; }
	bool getRMB() { return rmb; }
};

