#include "StatusLayer.h"


StatusLayer::StatusLayer(){};

StatusLayer::~StatusLayer(){};


bool StatusLayer::init(){
	if(!Layer::init()){
		return false;
	}

	this->showReadyStatus();
	return true;
}

void StatusLayer::showReadyStatus() {
	this->removeAllChildren();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	scoreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("font_048"));
	getreadySprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_ready"));
	tutorialSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("tutorial"));
	scoreSprite->setPosition(Point(originPoint.x + visibleSize.width / 2,originPoint.y + visibleSize.height *5/6));
	getreadySprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height *2/3));
	tutorialSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height * 1/2));
	this->addChild(scoreSprite);
	this->addChild(getreadySprite);
	this->addChild(tutorialSprite);
}

void StatusLayer::showStartStatus() {
	//ActionInterval * fadeout = FadeOut::create(1);
	/*CallFunc *actionDone = CallFunc::create(CC_CALLBACK_1(StatusLayer::clearSprite, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);*/
	this->getreadySprite->runAction(FadeOut::create(0.4));
	this->tutorialSprite->runAction(FadeOut::create(0.4));
	//this->getreadySprite->removeFromParent();
	//this->tutorialSprite->removeFromParent();
}

//void StatusLayer::clearSprite(Object* sender) {
//	Sprite *sprite = (Sprite*) sender;
//	sprite->removeFromParent();
//}

void StatusLayer::showOverStatus() {
	this->removeAllChildren();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();

	Sprite* gameoverSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameoverSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height * 5 / 7));
	this->addChild(gameoverSprite);

	Sprite* scorepanelSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	scorepanelSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height * 3 / 7));
	this->addChild(scorepanelSprite);

	//Sprite* cursocreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(""));
	//Sprite* bestscoreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(""));
	
	Sprite* startbtnSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	startbtnSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height * 1 / 7));
	this->addChild(startbtnSprite);
}

void StatusLayer::onGameStart(){
	this->showStartStatus();
}

void StatusLayer::onGamePlaying(int score){
	// Change the socre that displayed
}

void StatusLayer::onGameEnd(int curScore, int bestScore){
	this->showOverStatus();
}