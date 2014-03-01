#pragma once
#include "AtlasLoader.h"
#include "OptionDelegate.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class StatusLayer:public Layer,public OptionDelegate{
public:
	StatusLayer(void);
	~StatusLayer(void);
	virtual bool init();
	CREATE_FUNC(StatusLayer);

	void onGameStart();
	void onGamePlaying();
	void onGameEnd(int curSocre, int bestScore);
};
