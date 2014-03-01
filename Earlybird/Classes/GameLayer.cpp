#include "GameLayer.h"

GameLayer::GameLayer(){}

GameLayer::~GameLayer(){}

bool GameLayer::init(){
	if(Layer::init()) {
		this->gameStatus = GAME_STATUS_READY;
		this->score = 0;
		return true;
	}else {
		return false;
	}
}

void GameLayer::onTouch() {
	if(this->gameStatus == GAME_STATUS_READY) {
		this->delegator->onGameStart();
	}
}