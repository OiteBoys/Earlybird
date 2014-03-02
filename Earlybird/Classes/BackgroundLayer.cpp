#include "BackgroundLayer.h"
BackgroundLayer::BackgroundLayer(){};
BackgroundLayer::~BackgroundLayer(){};

bool BackgroundLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//get the current time, the background image will selected by current time day or night: bg_day or bg_night
	time_t t = time(NULL);
	tm* lt = localtime(&t);
	int hour = lt->tm_hour;
	//create the background image according to the current time;
	Sprite *background;
	if(hour >= 6 && hour <= 17){
		 background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
	}else{
		background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));
	}
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);

	this->landSpite1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->landSpite1->setAnchorPoint(Point::ZERO);
	this->landSpite1->setPosition(Point::ZERO);
	this->addChild(this->landSpite1,4);

	this->landSpite2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->landSpite2->setAnchorPoint(Point::ZERO);
	this->landSpite2->setPosition(this->landSpite1->getContentSize().width-2.0f,0);
	this->addChild(this->landSpite2,0);

	this->schedule(schedule_selector(BackgroundLayer::scrollLand),0.01f);
	return true;
}

void BackgroundLayer::scrollLand(float dt){
	this->landSpite1->setPositionX(this->landSpite1->getPositionX() - 2.0f);
	this->landSpite2->setPositionX(this->landSpite1->getPositionX() + this->landSpite1->getContentSize().width - 2.0f);
	if(this->landSpite2->getPositionX() == 0) {
		this->landSpite1->setPositionX(0);
	}else if(this->landSpite2->getPositionX() <= this->landSpite1->getContentSize().width/2.0f){
		// Avoid the black line bug
		this->landSpite2->setLocalZOrder(5);
	}else if(this->landSpite2->getPositionX() > this->landSpite1->getContentSize().width/2.0f) {
		// Avoid the black line bug
		this->landSpite2->setLocalZOrder(0);
	}
}

float BackgroundLayer::getLandHeight() {
    return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}