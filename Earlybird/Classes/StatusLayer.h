#pragma once

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "GameLayer.h"

using namespace std;
using namespace cocos2d;

class StatusLayer:public Layer,public StatusDelegate{
public:

	StatusLayer(void);

	~StatusLayer(void);

	virtual bool init();

	CREATE_FUNC(StatusLayer);

	void onGameStart();

	void onGamePlaying(int score);

	void onGameEnd(int curSocre, int bestScore);

private:
	void showReadyStatus();

	void showStartStatus();

	void showOverStatus();

	void loadWhiteSprite();

	void blinkFullScreen();

	void fadeInGameOver();

	void jumpToScorePanel();

	void fadeInRestartBtn();

	Sprite* scoreSprite;

	Sprite* getreadySprite;

	Sprite* tutorialSprite;

	Sprite* whiteSprite;

	/*void clearSprite(Object* sender);*/
};
