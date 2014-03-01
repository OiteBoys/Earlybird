#pragma once

#include "cocos2d.h"
#include "OptionLayer.h"
#include "BirdSprite.h"
using namespace cocos2d;

/**
* Define the game status
* GAME_STATUS_READY game is not start, just ready for payer to start.
* GAME_STATUS_START the game is started, and payer is paying this game.
* GAME_STATUS_OVER the player is lose this game, the game is over.
*/
typedef enum _game_status {
	GAME_STATUS_READY = 1,
	GAME_STATUS_START,
	GAME_STATUS_OVER
} GameStatus;

class StatusDelegate {
public:
	/**
	* When the game start, this method will be called
	*/
	virtual void onGameStart(void) = 0;

	/**
	* During paying, after the score changed, this method will be called
	*/
	virtual void onGamePlaying(int score) = 0;

	/**
	* When game is over, this method will be called
	*/
	virtual void onGameEnd(int curSocre, int bestScore) = 0;
};

class GameLayer : public Layer , public OptionDelegate{
public:
	GameLayer();

	~GameLayer();

	bool virtual init();

	CREATE_FUNC(GameLayer);

	/**
	* According to current game status, give the order to delegate.
	*/
	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	/**
	* @Override 
	* To see @OptionDelegate::onTouch 
	* User have touched the screen
	* This game, user just need only this method to control game
	*/
	void onTouch();

	/**
	* This layer need physical engine work
	*/
	void setPhyWorld(PhysicsWorld* world){this->world = world;}

private:
	 PhysicsWorld *world;

	 GameStatus gameStatus;

	 int score;

	 BirdSprite *bird;
};