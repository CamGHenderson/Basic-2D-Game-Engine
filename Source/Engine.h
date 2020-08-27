#pragma once

#include"Renderer.h"
#include"KeyInput.h"
#include"MouseInput.h"
#include"AudioPlayer.h"
#include"RandomUtil.h"

class Engine : public Renderer, public KeyInput, public MouseInput, public AudioPlayer, public RandomUtil
{
private:
	void applicationThread();
public:
	const char* run();
	void destroy();
	void onEngineRender() override;
};

