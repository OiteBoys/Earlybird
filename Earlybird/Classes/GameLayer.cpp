#include "GameLayer.h"

GameLayer::GameLayer(){}

GameLayer::~GameLayer(){}

bool GameLayer::init(){
	if(Layer::init()) {
		//get the origin point of the X-Y axis, and the visiable size of the screen
		Size visiableSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		this->gameStatus = GAME_STATUS_READY;
		this->score = 0;

		// Add the bird
		this->bird = BirdSprite::create();
		PhysicsBody *body = PhysicsBody::createBox(bird->getContentSize());
		body->setGravityEnable(false);
		body->addShape(PhysicsShapeBox::create(Size(20, 20), PHYSICSSHAPE_MATERIAL_DEFAULT, Point(10, 0)));
		this->bird->setPhysicsBody(body);
		this->bird->setPosition(origin.x + visiableSize.width*1/3,origin.y + visiableSize.height/2);
		this->bird->idle();
		this->addChild(bird);
		
		return true;
	}else {
		return false;
	}
}

void GameLayer::onTouch() {
	if(this->gameStatus == GAME_STATUS_READY) {
		this->delegator->onGameStart();
		this->bird->fly();
		this->gameStatus = GAME_STATUS_START;
	}else if(this->gameStatus == GAME_STATUS_START) {
		this->bird->getPhysicsBody()->setVelocity(Vect(0, 50));
	}
}