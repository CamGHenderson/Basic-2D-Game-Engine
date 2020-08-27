#include"Engine.h"


class Game : public Engine
{
private:
	Entity* player = NULL;
	SDL_Texture* grassTexture = NULL;
	SDL_Texture* treeTexture = NULL;
	Tile* grassTile[5000];
	Tile* treeTile[3000];
	Mix_Chunk* stepSound = NULL;
	double frameTime = 0;
	bool moving = false;
	bool playerRendered = false;
	enum class Direction
	{
		up,
		left,
		down,
		right
	};
	Direction direction = Direction::down;
	Camera* camera = NULL;
	float speed = 0.3f;
public:
	Game()
	{
		setSize(1280, 720);
		for (int i = 0; i < 5000; i++)
			grassTile[i] = NULL;
		for (int i = 0; i < 3000; i++)
			treeTile[i] = NULL;
	}

	bool onCreate() override
	{	
		grassTexture = loadTexture("Resources/Textures/GrassTile.png");
		if (!grassTexture)
			return false;

		treeTexture = loadTexture("Resources/Textures/Tree0.png", Color(163, 73, 164));
		if (!treeTexture)
			return false;

		for (int i = 0; i < 5000; i++)
		{
			grassTile[i] = new Tile(grassTexture, (float)((i % 100) * (32 * 2)), (float)((int)(i / 100) * (32 * 2)));
			grassTile[i]->scale(2, 2);
		}

		for (int i = 0; i < 3000; i++)
		{
			treeTile[i] = new Tile(treeTexture, (float)((getRandom(0, 100) % 100) * (32 * 4)), (float)(getRandom(0, 100) * (32 * 4)));
			treeTile[i]->scale(2, 2);
		}

		Sprite* sprite = loadSprite("Resources/Textures/PlayerSpriteSheetTest.png", Color(163, 73, 164));
		if (!sprite->getSpriteSheet())
			return false;
		player = new Entity(sprite, 500.0f, 100.0f);
		player->scale(2, 2);
		player->setPosition((float)(100 * grassTile[0]->getRect()->w/2), (float)(50 * grassTile[0]->getRect()->h / 2));

		stepSound = loadSound("Resources/Audio/step.wav");
		if (!stepSound)
			return false;

		camera = new Camera();
		setCamera(camera);
		camera->setBounds(0, 0, (float)(100 * grassTile[0]->getRect()->w - getWidth()), (float)(50 * grassTile[0]->getRect()->h - getHeight()));

		return true;
	}
	
	bool onRender() override
	{
		moving = false;

		playerRendered = false;

		if (getKeyDown(SDL_SCANCODE_D) && !getKeyDown(SDL_SCANCODE_A))
		{
			player->move((float)(speed * getDeltaTime()), 0);
			direction = Direction::right;
			moving = true;
			if (player->getX() > grassTile[5000 - 1]->getX() + grassTile[5000 - 1]->getRect()->w - (player->getSprite()->getAnimation()->getFrame().w*player->getScaleX()))
				player->setPosition(grassTile[5000 - 1]->getX() + grassTile[5000 - 1]->getRect()->w - (player->getSprite()->getAnimation()->getFrame().w * player->getScaleX()), player->getY());
		}

		if (getKeyDown(SDL_SCANCODE_A) && !getKeyDown(SDL_SCANCODE_D))
		{
			player->move(-(float)(speed * getDeltaTime()), 0);
			direction = Direction::left;
			moving = true;
			if (player->getX() < 0)
				player->setPosition(0, player->getY());
		}

		if (getKeyDown(SDL_SCANCODE_W) && !getKeyDown(SDL_SCANCODE_S))
		{
			player->move(0, -(float)(speed * getDeltaTime()));
			direction = Direction::up;
			moving = true;
			if (player->getY() < 0)
				player->setPosition(player->getX(), 0);
		}

		if (getKeyDown(SDL_SCANCODE_S) && !getKeyDown(SDL_SCANCODE_W))
		{
			player->move(0, (float)(speed * getDeltaTime()));
			direction = Direction::down;
			moving = true;
			if (player->getY() > grassTile[5000 - 1]->getY() + grassTile[5000 - 1]->getRect()->h - (player->getSprite()->getAnimation()->getFrame().h * player->getScaleY()))
				player->setPosition(player->getX(), grassTile[5000 - 1]->getY() + grassTile[5000 - 1]->getRect()->h - (player->getSprite()->getAnimation()->getFrame().h * player->getScaleY()));
		}

		if (moving)
		{
			switch (direction)
			{
			case Direction::up:
				player->getSprite()->setAnimation(5);
				break;
			case Direction::down:
				player->getSprite()->setAnimation(4);
				break;
			case Direction::right:
				player->getSprite()->setAnimation(6);
				break;
			case Direction::left:
				player->getSprite()->setAnimation(7);
				break;
			}
		}
		else
		{
			switch (direction)
			{
			case Direction::up:
				player->getSprite()->setAnimation(1);
				break;
			case Direction::down:
				player->getSprite()->setAnimation(0);
				break;
			case Direction::right:
				player->getSprite()->setAnimation(2);
				break;
			case Direction::left:
				player->getSprite()->setAnimation(3);
				break;
			}
		}

		frameTime += getDeltaTime();
		if (frameTime >= 50)
		{
			player->getSprite()->getAnimation()->nextFrame();
			frameTime = 0;
			if (moving)
				playSound(stepSound);
		}

		camera->setPosition(player->getX() - (getWidth()/2 - player->getSprite()->getAnimation()->getFrame().w/2),
			player->getY() - (getHeight()/2 - player->getSprite()->getAnimation()->getFrame().h / 2));
	
		for (int i = 0; i < 5000; i++)
			render(grassTile[i]);

		for (int i = 0; i < 3000; i++)
		{
			render(treeTile[i]);
			if (treeTile[i]->getY() < player->getY() && !playerRendered)
			{
				render(player);
				playerRendered = true;
			}
		}

		return true;
	}
	
	void onExit() override
	{
		
	}
};


int main(int argc, char* argv[]) 
{
	Game game;
	game.run();
	return 0;
}