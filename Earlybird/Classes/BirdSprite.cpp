#include "BirdSprite.h"

BirdSprite::BirdSprite() {
}

BirdSprite::~BirdSprite() {
}

bool BirdSprite::init() {
	if(Sprite::init()) {
		// init idle status

		//create the bird animation
		Animation* animation = this->createAnimation("bird2_%d", 3, 10);
		Animate* animate = Animate::create(animation);
		this->idleAction = RepeatForever::create(animate);

		// create the swing action
		ActionInterval *up = CCMoveBy::create(0.4f,Point(0, 8));
		ActionInterval *upBack= up->reverse();
//		ActionInterval *down = CCMoveBy::create(0.4f,Point(0, -4));
//		ActionInterval *downBack= down->reverse();
		this->swingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));
		return true;
	}else {
		return false;
	}
}

void BirdSprite::idle() {
	if (changeState(ACTION_STATE_IDLE)) {
        this->runAction(idleAction);
		this->runAction(swingAction);
    }
}

void BirdSprite::fly() {
	if(changeState(ACTION_STATE_FLY)) {
		this->stopAction(swingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

Animation* BirdSprite::createAnimation(const char *fmt, int count, float fps) {
    Animation *animation = Animation::create();
    animation->setDelayPerUnit(1/fps);
	for (int i = 0; i < count; i++){
		const char *filename = String::createWithFormat(fmt, i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

bool BirdSprite::changeState(ActionState state) {
    //this->stopAllActions();
    currentStatus = state;
    return true;
}