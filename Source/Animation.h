#pragma once

#include<SDL2/SDL.h>

#include<vector>

class Animation
{
private:
	std::vector<SDL_Rect> aFrames;
	int aCurrentFrame;
public:
	Animation(std::vector<SDL_Rect> frames);
	void nextFrame();
	void setFrame(int frame);
	SDL_Rect getFrame() { return aFrames.at(aCurrentFrame); }
	int getCurrentFrame() { return aCurrentFrame; }
	size_t getAmountOfFrames() { return aFrames.size(); }
};

