#pragma once
#include "AtlasLoader.h"
#include "WelcomeLayer.h"
#include "BackgroundLayer.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class WelcomeScene : public Scene{
public:
	WelcomeScene(void);
	~WelcomeScene(void);
	bool virtual init();
	CREATE_FUNC(WelcomeScene);
};