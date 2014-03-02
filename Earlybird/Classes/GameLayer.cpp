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
		PhysicsBody *body = PhysicsBody::create();
        body->addShape(PhysicsShapeCircle::create(15));
        body->setDynamic(true);
		body->setGravityEnable(false);
		this->bird->setPhysicsBody(body);
		this->bird->setPosition(origin.x + visiableSize.width*1/3 - 5,origin.y + visiableSize.height/2 + 5);
		this->bird->idle();
		this->addChild(bird);
        
        // Add the ground
        this->groundNode = Node::create();
        float landHeight = BackgroundLayer::getLandHeight();
        auto groundBody = PhysicsBody::create();
        groundBody->addShape(PhysicsShapeBox::create(Size(288, landHeight)));
        groundBody->setDynamic(false);
        groundBody->setLinearDamping(1.0f);
        this->groundNode->setPhysicsBody(groundBody);
        this->groundNode->setPosition(144, landHeight/2);
        this->addChild(this->groundNode);
        
        this->scheduleUpdate();
		
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
		this->bird->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
}

void GameLayer::rotateBird() {
    float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
    this->bird->setRotation(fmin(fmax(-90, (verticalSpeed*0.2 + 30)), 30));
}


void GameLayer::update(float delta) {
    if (this->gameStatus == GAME_STATUS_START) {
        this->rotateBird();
    }
}
