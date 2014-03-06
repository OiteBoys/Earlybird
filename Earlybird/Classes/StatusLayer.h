#pragma once

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "Number.h"

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

	void onGameEnd(int curScore, int bestScore);

private:
	void showReadyStatus();

	void showStartStatus();

	void showOverStatus(int curScore, int bestScore);

	void loadWhiteSprite();

	stack<string> getScoreByDigit(int score);

	stack<string> getScoreBySmallDigit(int score);

	void blinkFullScreen();

	void fadeInGameOver();

	void jumpToScorePanel();

	void fadeInRestartBtn();

	void menuRestartCallback(Object *sender);

	Sprite* scoreSprite;

	Sprite* getreadySprite;

	Sprite* tutorialSprite;

	Sprite* whiteSprite;

	/*void clearSprite(Object* sender);*/
};
