#include "StatusLayer.h"


StatusLayer::StatusLayer(){};

StatusLayer::~StatusLayer(){};


bool StatusLayer::init(){
	if(!Layer::init()){
		return false;
	}
	// init numbers
	Number::getInstance()->loadNumber("font", "font_0%02d", 48);
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
	this->getreadySprite->runAction(FadeOut::create(0.4f));
	this->tutorialSprite->runAction(FadeOut::create(0.4f));
}

void StatusLayer::showOverStatus(int curScore, int bestScore) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	stack<string> curScoreStack,bestScoreStack;
	this->removeChild(scoreSprite);

	this->blinkFullScreen();
	this->fadeInGameOver();
	this->jumpToScorePanel();
	this->fadeInRestartBtn();

	//display the current score on the score panel
	curScoreStack = this->getScoreBySmallDigit(curScore);
	Sprite* curScoreSprite = Sprite::create();
	while(!curScoreStack.empty()){
		string tempString = curScoreStack.top();
		curScoreStack.pop();
		Sprite* tmpScoreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(tempString));
		int childCount = curScoreSprite->getChildrenCount();
		tmpScoreSprite->setPosition(Point(0,0));
		if(childCount == 0){
			tmpScoreSprite->setPosition(Point(0,0));
		}else{
			tmpScoreSprite->setPosition(Point(childCount * tmpScoreSprite->getContentSize().width + 1.0f, 0));
		}
		curScoreSprite->addChild(tmpScoreSprite);
	}
	curScoreSprite->setPosition(Point(originPoint.x + visibleSize.width * 3 / 4 - 4.0f, originPoint.y + visibleSize.height *  1 / 2 + 17.0f ));
	this->addChild(curScoreSprite);

	//display the  best score on the score panel
	bestScoreStack = this->getScoreBySmallDigit(bestScore);
	Sprite* bestScoreSprite = Sprite::create();
	while(!bestScoreStack.empty()){
		string tempString = bestScoreStack.top();
		bestScoreStack.pop();
		Sprite* tmpScoreSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(tempString));
		int childCount = bestScoreSprite->getChildrenCount();
		tmpScoreSprite->setPosition(Point(0,0));
		if(childCount == 0){
			tmpScoreSprite->setPosition(Point(0,0));
		}else{
			tmpScoreSprite->setPosition(Point(childCount * tmpScoreSprite->getContentSize().width + 1.0f,0));
		}
		bestScoreSprite->addChild(tmpScoreSprite);
	}
	bestScoreSprite->setPosition(Point(originPoint.x + visibleSize.width * 3 / 4 - 4.0f, originPoint.y + visibleSize.height *  1 / 2 - 27.0f ));
	this->addChild(bestScoreSprite);
	//display the gold silver or bronze golden iron
	string medalsName = "medals_0";
	if(curScore < 10){//iron medals
		medalsName = "medals_0";
	}else if(curScore >= 10 && curScore < 30){//bronze medals
		medalsName = "medals_1";
	}else if(curScore >=30 && curScore <50){//silver medals
		medalsName = "medals_2";
	}else{//golden medals
		medalsName = "medals_3";
	}
	Sprite* medalsSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(medalsName));
	medalsSprite->setPosition(Point(originPoint.x + visibleSize.width * 2 / 7 - 2.0f, originPoint.y + visibleSize.height * 1 / 2 - 3.0f));
	this->addChild(medalsSprite);

	//if the current score is higher than the best score.
	//the panel will appear a "new" tag.
	if(curScore > bestScore){
		Sprite* newTagSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("new"));
		newTagSprite->setPosition(Point(originPoint.x + visibleSize.width * 3 / 4 - 25.0f, originPoint.y + visibleSize.height *  1 / 2 + 17.0f ));
		this->addChild(newTagSprite);
	}
}

void StatusLayer::onGameStart(){
	this->showStartStatus();
}

void StatusLayer::onGamePlaying(int score){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	this->removeChild(scoreSprite);
	this->scoreSprite = (Sprite* )Number::getInstance()->convert("font", score);
	scoreSprite->setPosition(Point(originPoint.x + visibleSize.width / 2,originPoint.y + visibleSize.height *5/6));
	this->addChild(scoreSprite);
}

void StatusLayer::onGameEnd(int curScore, int bestScore){
	this->showOverStatus(curScore,bestScore);
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
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
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
	//FiniteTimeAction* seq = Sequence::create(gameoverFadeIn,CC_CALLBACK_0(StatusLayer::jumpToScorePanel,this),NULL);
	gameoverSprite->runAction(gameoverFadeIn);
}

void StatusLayer::jumpToScorePanel(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Sprite* scorepanelSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	scorepanelSprite->setPosition(Point(originPoint.x + visibleSize.width / 2, originPoint.y - scorepanelSprite->getContentSize().height));
   	this->addChild(scorepanelSprite);
	auto scorePanelMoveTo = MoveTo::create(1,Point(originPoint.x + visibleSize.width / 2,originPoint.y + visibleSize.height/2));
	//Action* seq = Sequence::create(scorePanelMoveTo,CC_CALLBACK_0(StatusLayer::fadeInRestartBtn,this),NULL);
	scorepanelSprite->runAction(scorePanelMoveTo);
}

void StatusLayer::fadeInRestartBtn(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Node * tmpNode = Node::create();
	//create the restart menu;
	Sprite* restartBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* restartBtnActive = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	restartBtnActive->setPositionY(-4);
	auto  menuItem = MenuItemSprite::create(restartBtn,restartBtnActive,NULL,CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));
    auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(originPoint.x + visibleSize.width / 2 - restartBtn->getContentSize().width / 2, originPoint.y + visibleSize.height * 2 / 7));
	tmpNode->addChild(menu);
	//create the rate button. however ,this button is not available yet = =
	Sprite* rateBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_score"));
	rateBtn->setPosition(Point(originPoint.x + visibleSize.width / 2 + rateBtn->getContentSize().width / 2, originPoint.y + visibleSize.height * 2 / 7));
	tmpNode->addChild(rateBtn);
	this->addChild(tmpNode);
	//fade in the two buttons
	auto fadeIn = FadeIn::create(5);
	tmpNode->runAction(fadeIn);
}

void StatusLayer::menuRestartCallback(Object* pSender){
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

stack<string> StatusLayer::getScoreByDigit(int score){
	string scoreImgName;
	stack<string> scoreStringStack;
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
	return scoreStringStack;
}

stack<string> StatusLayer::getScoreBySmallDigit(int score){
		string scoreImgName;
	stack<string> scoreStringStack;
	//get the score number by each digit
	while(score){
		int temp = score % 10;
		score /= 10;
		switch(temp){
			case 0:
				scoreImgName = "number_score_00";break;
			case 1:
				scoreImgName = "number_score_01";break;
			case 2:
				scoreImgName = "number_score_02";break;
			case 3:
				scoreImgName = "number_score_03";break;
			case 4:
				scoreImgName = "number_score_04";break;
			case 5:
				scoreImgName = "number_score_05";break;
			case 6:
				scoreImgName = "number_score_06";break;
			case 7:
				scoreImgName = "number_score_07";break;
			case 8:
				scoreImgName = "number_score_08";break;
			case 9:
				scoreImgName = "number_score_09";break;
			default:
				scoreImgName = "number_score_00";break;
		};
		scoreStringStack.push(scoreImgName);
	}
	return scoreStringStack;
}