#include "Renderer.h"

#include<SDL2/SDL_image.h>

#include<cmath>

Renderer::Renderer()
{
	rTitle = "2D Game Engine";
	rWidth = 800;
	rHeight = 600;
	rRunning = false;
	rExit = "";
	rRenderer = NULL;
	rDeltaTime = 0;
	rRectBuffer = SDL_Rect();
	rCamera = NULL;
}

void Renderer::runRenderer() 
{
	rRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		rExit = "SDL Failed To Initialize.";
		return;
	}

	SDL_Window* rWindow = SDL_CreateWindow(rTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rWidth, rHeight, SDL_WINDOW_SHOWN);
	if (!rWindow)
	{
		rExit = "SDL Window Failed To Be Created.";
		return;
	}

	rRenderer = SDL_CreateRenderer(rWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!rRenderer)
	{
		rExit = "SDL Renderer Failed To Be Created.";
		return;
	}

	int imgFlag = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlag) & IMG_INIT_PNG))
	{
		rExit = "SDL Image Failed To Initialize.";
		return;
	}

	if (!onCreate())
		rRunning = false;

	Uint64 time = SDL_GetPerformanceCounter();
	Uint64 lastTime = time;

	SDL_Event rEvent;
	while (rRunning)
	{
		while(SDL_PollEvent(&rEvent) != 0)
			switch (rEvent.type)
			{
			case SDL_QUIT:
				rRunning = false;
				break;
			default:
				break;
			}
		SDL_RenderClear(rRenderer);
		time = SDL_GetPerformanceCounter();
		rDeltaTime = (double)((time - lastTime) * 1000/ (double)SDL_GetPerformanceFrequency());
		onEngineRender();
		if (!onRender())
			rRunning = false;
		lastTime = time;
		SDL_RenderPresent(rRenderer);
	}

	for (SDL_Texture* texture : rTextures)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}

	SDL_DestroyRenderer(rRenderer);
	SDL_DestroyWindow(rWindow);
	rRenderer = NULL;
	rWindow = NULL;

	IMG_Quit();
	SDL_Quit();

	onExit();
	rExit = "Program Exited Without Errors";
}

void Renderer::destroyRenderer() 
{
	rRunning = false;
}

void Renderer::setTitle(const char* title)
{
	rTitle = title;
}

void Renderer::setSize(int width, int height)
{
	rWidth = width;
	rHeight = height;
}

void Renderer::render(Entity* entity)
{
	entity->getRect()->w = entity->getSprite()->getAnimation()->getFrame().w * (int)std::round(entity->getScaleX());
	entity->getRect()->h = entity->getSprite()->getAnimation()->getFrame().h * (int)std::round(entity->getScaleY());
	entity->getRotationAxisBuffer()->x = entity->getRotationAxis()->x * (int)std::round(entity->getScaleX());
	entity->getRotationAxisBuffer()->y = entity->getRotationAxis()->y * (int)std::round(entity->getScaleY());

	if (rCamera != NULL)
	{
		rRectBuffer.x = entity->getRect()->x - (int)std::round(rCamera->getX());
		rRectBuffer.y = entity->getRect()->y - (int)std::round(rCamera->getY());
		rRectBuffer.w = entity->getRect()->w;
		rRectBuffer.h = entity->getRect()->h;
		SDL_RenderCopyEx(rRenderer, entity->getSprite()->getSpriteSheet(), &entity->getSprite()->getAnimation()->getFrame(),
			&rRectBuffer, entity->getRotation(), entity->getRotationAxisBuffer(), entity->getFlip());
	}
	else
	{
		SDL_RenderCopyEx(rRenderer, entity->getSprite()->getSpriteSheet(), &entity->getSprite()->getAnimation()->getFrame(),
			entity->getRect(), entity->getRotation(), entity->getRotationAxisBuffer(), entity->getFlip());
	}
}

void Renderer::render(Tile* tile)
{
	if (rCamera != NULL)
	{
		rRectBuffer.x = tile->getRect()->x - (int)std::round(rCamera->getX());
		rRectBuffer.y = tile->getRect()->y - (int)std::round(rCamera->getY());
		rRectBuffer.w = tile->getRect()->w;
		rRectBuffer.h = tile->getRect()->h;
		SDL_RenderCopy(rRenderer, tile->getTexture(), NULL, &rRectBuffer);
	}
	else
	{
		SDL_RenderCopy(rRenderer, tile->getTexture(), NULL, tile->getRect());
	}
}

void Renderer::render(UIComponent* component)
{
	SDL_RenderCopy(rRenderer, component->getTexture(), NULL, component->getRect());
}

void Renderer::setCamera(Camera* camera)
{
	rCamera = camera;
}

SDL_Color* Renderer::getSurfacePixel(SDL_Surface* surface, int x, int y)
{
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * (int)surface->format->BytesPerPixel;
	Uint32 data = *(Uint32*)p;
	SDL_Color* pixel = new SDL_Color();
	SDL_GetRGB(data, surface->format, &pixel->r, &pixel->g, &pixel->b);
	return pixel;
}

SDL_Texture* Renderer::loadTexture(const char* file)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(file);
	if (!loadedSurface)
		return NULL;

	texture = SDL_CreateTextureFromSurface(rRenderer, loadedSurface);
	if (!texture)
		return NULL;
	rTextures.push_back(texture);

	SDL_FreeSurface(loadedSurface);
	
	return texture;
}

SDL_Texture* Renderer::loadTexture(const char* file, Color bg)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(file);
	if (!loadedSurface)
		return NULL;

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, bg.red, bg.green, bg.blue));

	texture = SDL_CreateTextureFromSurface(rRenderer, loadedSurface);
	if (!texture)
		return NULL;
	rTextures.push_back(texture);

	SDL_FreeSurface(loadedSurface);

	return texture;
}

Sprite* Renderer::loadSprite(const char* file, Color bg)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(file);
	if (!loadedSurface)
		return NULL;

	bool completeLine = false;

	std::vector<Animation> animations;
	SDL_Color* p = getSurfacePixel(loadedSurface, 0, 0);
	std::vector<int> rowEndPoints;
	for (int y = 0; y < loadedSurface->h; y++)
		for (int x = 0; x < loadedSurface->w; x++)
		{
			p = getSurfacePixel(loadedSurface, x, y);
			if (p->r != bg.red || p->g != bg.green || p->b != bg.blue)
			{
				completeLine = false;
				break;
			}
			else if (x == loadedSurface->w - 1)
			{
				rowEndPoints.push_back(y);
				completeLine = true;
			}
		}
	rowEndPoints.push_back(loadedSurface->h);

	completeLine = false;
	for (int a = 0; a < rowEndPoints.size(); a++)
	{
		std::vector<SDL_Rect> frames;
		int dist = 0;
		int total = 0;
		for (int x = 0; x < loadedSurface->w; x++)
		{
			for (int y = 0; y < rowEndPoints.at(a); y++)
			{
				p = getSurfacePixel(loadedSurface, x, y);
				if (p->r != bg.red || p->g != bg.green || p->b != bg.blue)
				{
					completeLine = false;
					break;
				}
				else if (y == rowEndPoints.at(a) - 1 && !completeLine)
				{
					SDL_Rect frame;
					frame.x = total;
					frame.y = (a > 0) ? rowEndPoints.at(a - 1) : 0;
					frame.w = dist;
					frame.h = (a > 0) ? rowEndPoints.at(a) - rowEndPoints.at(a-1) : rowEndPoints.at(a);
					if (frames.size() > 0)
					{
						frame.x++;
						frame.w--;
					}
					if (animations.size() > 0)
					{
						frame.y++;
						frame.h--;
					}
					frames.push_back(frame);
					total += dist;
					dist = 0;
					completeLine = true;
				}
			}
			dist++;
		}
		animations.push_back(Animation(frames));
	}
	delete p;

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, bg.red, bg.green, bg.blue));

	texture = SDL_CreateTextureFromSurface(rRenderer, loadedSurface);
	if (!texture)
		return NULL;
	rTextures.push_back(texture);

	SDL_FreeSurface(loadedSurface);

	return new Sprite(texture, animations);
}