#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "StatusLayer.h"
#include "OptionLayer.h"

using namespace cocos2d;

class GameScene:public Scene{
public:
	GameScene();

	~GameScene();

	bool virtual init();
    
    void restart();

	CREATE_FUNC(GameScene);
};