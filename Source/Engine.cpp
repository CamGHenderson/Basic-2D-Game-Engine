#include "Engine.h"

#include<thread>

void Engine::applicationThread() 
{
	runRenderer();
	cleanUp();
}

const char* Engine::run()
{
	std::thread runThread(&Engine::applicationThread, this);

	const char* exit;

	while (true)
	{
		if ((exit = getRendererExit()) != "")
			break;

		if ((exit = getError()) != "")
			break;
	}

	runThread.detach();

	return exit;
}

void Engine::destroy()
{
	destroyRenderer();
}

void Engine::onEngineRender()
{
	KeyInput::update();
	MouseInput::update();
}