#pragma once
#include "cocos2d.h"
#include "AtlasLoader.h"

using namespace cocos2d;

typedef enum{
    ACTION_STATE_IDLE,
	ACTION_STATE_FLY
} ActionState;

class BirdSprite : public Sprite {
public:
	/**
	* Default construct
	*/
	BirdSprite();

	/**
	* Default distruct
	*/
	~BirdSprite();

	/**
	* Cocos2d construct
	*/
	bool virtual init();

	CREATE_FUNC(BirdSprite);

	/**
	* The bird fly with swing, but do not effected by gravity.
	*/
	void idle();

	/**
	* The bird fly drived by player, effected by gravity. need physical support.
	*/
	void fly();
	
protected:
	/**
	* This method can create a frame animation with the likey name texture.
	*/
    static cocos2d::Animation *createAnimation(const char *fmt, int count, float fps);

private:
	/**
	* This method change current status. called by fly and idle etc.
	*/
	bool changeState(ActionState state);

	Action* idleAction;

	//Action* flyAction;

	Action* swingAction;

	ActionState currentStatus;
};