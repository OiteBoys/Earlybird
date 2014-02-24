#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
	bool virtual init();
	CREATE_FUNC(MenuScene);
};

class MenuLayer : public Layer
{
public:
	MenuLayer();
	~MenuLayer();
	bool virtual init();
	CREATE_FUNC(MenuLayer);
};