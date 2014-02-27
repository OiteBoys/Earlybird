#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class GameScene:public Scene{
public:
	GameScene();
	~GameScene();
	bool virtual init();
	void menuStartCallback(Object* pSender);
	CREATE_FUNC(GameScene);
};