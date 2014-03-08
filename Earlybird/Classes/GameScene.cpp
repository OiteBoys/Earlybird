#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init(){
	if(Scene::initWithPhysics()){
		//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
        this->getPhysicsWorld()->setGravity(Vect(0, -900));

		// Add the background
		auto backgroundLayer = BackgroundLayer::create();
		if(backgroundLayer) {
			this->addChild(backgroundLayer);
		}

		auto statusLayer = StatusLayer::create();

		// Add the main game layer
		auto gameLayer = GameLayer::create();
		if(gameLayer) {
			gameLayer->setPhyWorld(this->getPhysicsWorld());
			gameLayer->setDelegator(statusLayer);
			this->addChild(gameLayer);
		}

		// Add the game status layer to show the score and game status
		if(statusLayer) {
			this->addChild(statusLayer);
		}

		// Add operation layer to control the game
		auto optionLayer = OptionLayer::create();
		if(optionLayer) {
			optionLayer->setDelegator(gameLayer);
			this->addChild(optionLayer);
		}
		return true;
	}else {
		return false;
	}
}

void GameScene::restart() {
    this->removeAllChildrenWithCleanup(true);
    this->init();
}
