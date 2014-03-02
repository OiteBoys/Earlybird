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
        body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
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
        
        // init land
        this->landSpite1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
        this->landSpite1->setAnchorPoint(Point::ZERO);
        this->landSpite1->setPosition(Point::ZERO);
        this->addChild(this->landSpite1,40);
        
        this->landSpite2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
        this->landSpite2->setAnchorPoint(Point::ZERO);
        this->landSpite2->setPosition(this->landSpite1->getContentSize().width-2.0f,0);
        this->addChild(this->landSpite2,30);
        
        this->schedule(schedule_selector(GameLayer::scrollLand),0.01f);
        
        this->scheduleUpdate();
		
		return true;
	}else {
		return false;
	}
}

void GameLayer::scrollLand(float dt){
	this->landSpite1->setPositionX(this->landSpite1->getPositionX() - 2.0f);
	this->landSpite2->setPositionX(this->landSpite1->getPositionX() + this->landSpite1->getContentSize().width - 2.0f);
	if(this->landSpite2->getPositionX() == 0) {
		this->landSpite1->setPositionX(0);
	}else if(this->landSpite2->getPositionX() <= this->landSpite1->getContentSize().width/2.0f){
		// Avoid the black line bug
		this->landSpite2->setLocalZOrder(50);
	}else if(this->landSpite2->getPositionX() > this->landSpite1->getContentSize().width/2.0f) {
		// Avoid the black line bug
		this->landSpite2->setLocalZOrder(30);
	}
    
    // move the pips
    for (auto singlePip : this->pips) {
        singlePip->setPositionX(singlePip->getPositionX() - 2);
        if(singlePip->getPositionX() < -PIP_WIDTH) {
            Size visibleSize = Director::getInstance()->getVisibleSize();
            singlePip->setPositionX(visibleSize.width);
            singlePip->setPositionY(this->getRandomHeight());
        }
    }
}

void GameLayer::onTouch() {
	if(this->gameStatus == GAME_STATUS_READY) {
		this->delegator->onGameStart();
		this->bird->fly();
		this->gameStatus = GAME_STATUS_START;
        this->createPips();
	}else if(this->gameStatus == GAME_STATUS_START) {
		this->bird->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
}

void GameLayer::rotateBird() {
    float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
    this->bird->setRotation(min(max(-90, (verticalSpeed*0.2 + 30)), 30));
}


void GameLayer::update(float delta) {
    if (this->gameStatus == GAME_STATUS_START) {
        this->rotateBird();
		this->checkHit();
    }
}

void GameLayer::createPips() {
    // Create the pips
    for (int i = 0; i < PIP_COUNT; i++) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Sprite *pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
        Sprite *pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
        Node *singlePip = Node::create();
        
        // bind to pair
        pipDown->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
        singlePip->addChild(pipDown);
        singlePip->addChild(pipUp);
        singlePip->setPosition(visibleSize.width + i*PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());
        
        this->addChild(singlePip);
//        int distance = singlePip->getPositionX() + PIP_WIDTH;
//        Action *moveTo = MoveTo::create(distance/PIP_SHIFT_SPEED, Point(-PIP_WIDTH, singlePip->getPositionY()));
//        singlePip->runAction(moveTo);
        this->pips.push_back(singlePip);
    }
}

int GameLayer::getRandomHeight() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}

void GameLayer::checkHit() {
    if (this->bird->getPositionY() < this->landSpite1->getContentSize().height + BIRD_RADIUS) {
		this->gameOver();
    }
}

void GameLayer::gameOver() {
	 this->delegator->onGameEnd(this->score, 0);
	 this->gameStatus = GAME_STATUS_OVER;
}
