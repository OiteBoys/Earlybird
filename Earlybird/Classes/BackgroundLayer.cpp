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

	
	return true;
}

float BackgroundLayer::getLandHeight() {
    return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}