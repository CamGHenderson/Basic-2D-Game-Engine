#pragma once

#include<SDL2/SDL.h>

#include<vector>

#include"Animation.h"

class Sprite
{
private:
	SDL_Texture* sSpriteSheet;
	std::vector<Animation> sAnimations;
	int sCurrentAnimation;
public:
	Sprite() { sSpriteSheet = NULL; sAnimations = std::vector<Animation>(); }
	Sprite(SDL_Texture* spriteSheet, std::vector<Animation> animation);
	void setAnimation(int animation);
	Animation* getAnimation() { return &sAnimations.at(sCurrentAnimation); }
	std::vector<Animation> getAnimations() { return sAnimations; }
	size_t getAnimationAmount() { return sAnimations.size(); }
	SDL_Texture* getSpriteSheet() { return sSpriteSheet; }
};

