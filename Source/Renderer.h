#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#include<vector>

#include"ControllerInput.h"
#include"Entity.h"
#include"Sprite.h"
#include"Color.h"
#include"Tile.h"
#include"UIComponent.h"
#include"Camera.h"

class Renderer
{
private:
	const char* rTitle;
	int rWidth;
	int rHeight;
	bool rRunning;
	const char* rExit;
	SDL_Renderer* rRenderer;
	ControllerInput* rController;
	std::vector<SDL_Texture*> rTextures;
	std::vector<TTF_Font*> rFonts;
	double rDeltaTime;
	SDL_Rect rRectBuffer;
	Camera* rCamera;
public:
	Renderer();
protected:
	void runRenderer();
	void destroyRenderer();
	const char* getRendererExit() { return rExit; };
public:
	virtual bool onCreate() { return false; }
	virtual bool onRender() { return false; }
	virtual void onExit() {}
	virtual void onEngineRender() {}
	void setTitle(const char* title);
	const char* getTitle() { return rTitle; }
	void setSize(int width, int height);
	int getWidth() { return rWidth; }
	int getHeight() { return rHeight; }
	void render(Entity* entity);
	void render(Tile* tile);
	void render(UIComponent* component);
	void setCamera(Camera* camera);
	double getDeltaTime() { return rDeltaTime; }
	ControllerInput* getController() { return rController; }
private:
	SDL_Color* getSurfacePixel(SDL_Surface* surface, int x, int y);
public:
	SDL_Texture* loadTexture(const char* file);
	SDL_Texture* loadTexture(const char* file, Color bg);
	TTF_Font* loadFont(const char* file, int size);
	SDL_Texture* loadTextureFromText(const char* text, TTF_Font* font, Color color);
	Sprite* loadSprite(const char* file, Color bg);
};

