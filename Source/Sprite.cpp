#include "Sprite.h"

Sprite::Sprite(SDL_Texture* spriteSheet, std::vector<Animation> animations)
{
	sSpriteSheet = spriteSheet;
	sAnimations = animations;
	sCurrentAnimation = 0;
}

void Sprite::setAnimation(int animation)
{
	sCurrentAnimation = animation;
}