#pragma once

#include "AtlasLoader.h"

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class WelcomeLayer : public Layer{
public:
	WelcomeLayer();
	~WelcomeLayer();
	bool virtual init();
};