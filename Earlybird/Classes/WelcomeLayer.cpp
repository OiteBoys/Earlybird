#include "WelcomeLayer.h"

WelcomeLayer::WelcomeLayer(){};

WelcomeLayer::~WelcomeLayer(){};

bool WelcomeLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//get the origin point of the X-Y axis, and the visiable size of the screen
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

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

	//add the word game-title to the current scene
	Sprite *title  = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
	title->setPosition(Point(origin.x + visiableSize.width/2 , (visiableSize.height * 5) / 7));
	this->addChild(title);

	//add the start-menu to the current scene
	Sprite *startButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite *activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	activeStartButton->setPositionY(5);
	auto menuItem  = MenuItemSprite::create(startButton,activeStartButton,NULL,CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
	menuItem->setPosition(Point(origin.x + visiableSize.width/2 ,origin.y + visiableSize.height*2/5));

    auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(origin.x ,origin.y));
	this->addChild(menu,1);

	//create a bird and set the position in the center of the screen
	this->bird = BirdSprite::getInstance();
	this->bird->createBird();
	this->bird->setTag(BIRD_SPRITE_TAG);
	this->bird->setPosition(Point(origin.x + visiableSize.width / 2,origin.y + visiableSize.height*3/5 - 10));
	this->bird->idle();
	this->addChild(this->bird);

	// Add the land
	this->land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land1->setAnchorPoint(Point::ZERO);
	this->land1->setPosition(Point::ZERO);
	this->addChild(this->land1);

	this->land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
	this->land2->setAnchorPoint(Point::ZERO);
	this->land2->setPosition(this->land1->getContentSize().width - 2.0f, 0);
	this->addChild(this->land2);

	this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);

	//add the copyright-text to the current scne
	Sprite *copyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
	copyright->setPosition(Point(origin.x + visiableSize.width/2, origin.y + visiableSize.height/6));
	this->addChild(copyright, 10);

	return true;
}

void WelcomeLayer::scrollLand(float dt){
	this->land1->setPositionX(this->land1->getPositionX() - 2.0f);
	this->land2->setPositionX(this->land1->getPositionX() + this->land1->getContentSize().width - 2.0f);

	if(this->land2->getPositionX() == 0) {
		this->land1->setPositionX(0);
	}
}

void WelcomeLayer::menuStartCallback(Object *sender){
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}
