#pragma once
#include "AtlasLoader.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class WelcomeScene : public Scene{
public:
	WelcomeScene();
	~WelcomeScene();
	bool virtual init();
	CREATE_FUNC(WelcomeScene);
};