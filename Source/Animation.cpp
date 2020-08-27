#include "Animation.h"

Animation::Animation(std::vector<SDL_Rect> frames)
{
	aFrames = frames;
	aCurrentFrame = 0;
}

void Animation::nextFrame() 
{
	aCurrentFrame++;
	if (aCurrentFrame >= aFrames.size())
		aCurrentFrame = 0;
}

void Animation::setFrame(int frame)
{
	aCurrentFrame = frame;
}