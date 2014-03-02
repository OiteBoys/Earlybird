#include "StatusLayer.h"


StatusLayer::StatusLayer(){};

StatusLayer::~StatusLayer(){};


bool StatusLayer::init(){
	if(!Layer::init()){
		return false;
	}
	this->showReadyStatus();
	this->loadWhiteSprite();
	return true;
}

void StatusLayer::showReadyStatus() {
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
	this->getreadySprite->runAction(FadeOut::create(0.4));
	this->tutorialSprite->runAction(FadeOut::create(0.4));

}

void StatusLayer::showOverStatus() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	this->removeChild(scoreSprite);


	this->blinkFullScreen();
	this->fadeInGameOver();
	this->jumpToScorePanel();

	//Sprite* scorepanelSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	//scorepanelSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height * 3 / 7));
	//this->addChild(scorepanelSprite);

	//Sprite* cursocreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(""));
	//Sprite* bestscoreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(""));
	
	//Sprite* startbtnSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	//startbtnSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height * 1 / 7));
	//this->addChild(startbtnSprite);
}

void StatusLayer::onGameStart(){
	this->showStartStatus();
}

void StatusLayer::onGamePlaying(int score){
	// Change the socre that displayed
	string scoreImgName;
	stack<string> scoreStringStack;
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//get the score number by each digit
	while(score){
		int temp = score % 10;
		score /= 10;
		switch(temp){
			case 0:
				scoreImgName = "font_048";break;
			case 1:
				scoreImgName = "font_049";break;
			case 2:
				scoreImgName = "font_050";break;
			case 3:
				scoreImgName = "font_051";break;
			case 4:
				scoreImgName = "font_052";break;
			case 5:
				scoreImgName = "font_053";break;
			case 6:
				scoreImgName = "font_054";break;
			case 7:
				scoreImgName = "font_055";break;
			case 8:
				scoreImgName = "font_056";break;
			case 9:
				scoreImgName = "font_057";break;
			default:
				scoreImgName = "font_048";break;
		};
		scoreStringStack.push(scoreImgName);
	}
	this->removeChild(scoreSprite);
	scoreSprite = Sprite::create();
	//get the sprite of every digit
	while(!scoreStringStack.empty()){
		string tempString = scoreStringStack.top();
		scoreStringStack.pop();
		Sprite* tmpScoreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(tempString));
		int childCount = scoreSprite->getChildrenCount();
		tmpScoreSprite->setPosition(Point(0,0));
		if(childCount == 0){
			tmpScoreSprite->setPosition(Point(0,0));
		}else{
			tmpScoreSprite->setPosition(Point(childCount * tmpScoreSprite->getContentSize().width + 2.0f, 0));
		}
		scoreSprite->addChild(tmpScoreSprite);
	}
	scoreSprite->setPosition(Point(originPoint.x + visibleSize.width / 2,originPoint.y + visibleSize.height *5/6));
	this->addChild(scoreSprite);
}

void StatusLayer::onGameEnd(int curScore, int bestScore){
	this->showOverStatus();
}

void StatusLayer::loadWhiteSprite(){
	//this white sprite is used for blinking the screen for a short while
	whiteSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("white"));
	whiteSprite->setScale(100);
	whiteSprite->setOpacity(0);
	this->addChild(whiteSprite,10000);
}

void StatusLayer::blinkFullScreen(){
	//display a flash blink
	auto fadeOut = FadeOut::create(0.1);
	auto fadeIn = FadeIn::create(0.1);
	auto blinkAction = Sequence::create(fadeIn,fadeOut,NULL);
	whiteSprite->runAction(blinkAction);
}
void StatusLayer::fadeInGameOver(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Sprite* gameoverSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameoverSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y + visibleSize.height *2/3));
	this->addChild(gameoverSprite);
	auto gameoverFadeIn = FadeIn::create(1);
	gameoverSprite->runAction(gameoverFadeIn);
}

void StatusLayer::jumpToScorePanel(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Sprite* scorepanelSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	scorepanelSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y - scorepanelSprite->getContentSize().height));
    this->addChild(scorepanelSprite);
	auto scorePanelMoveTo = MoveTo::create(1,Point(originPoint.x + visibleSize.width / 2,originPoint.y + visibleSize.height/2));
	scorepanelSprite->runAction(scorePanelMoveTo);
}