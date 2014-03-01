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
	Sprite* scoreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("number_score_00"));
	Sprite* getreadySprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_ready"));
	Sprite* tutorialSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("tutorial"));
	scoreSprite->setPosition(Point(originPoint.x + visibleSize.width / 2,originPoint.y + visibleSize.height *4 / 5));
	getreadySprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height *3 / 5));
	tutorialSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height * 2 / 5));
	this->addChild(scoreSprite);
	this->addChild(getreadySprite);
	this->addChild(tutorialSprite);
}

void StatusLayer::showStartStatus() {
	this->removeAllChildren();
}

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