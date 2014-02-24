#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init(){
	if(Scene::init()){
		return true;
	}else {
		return false;
	}
}