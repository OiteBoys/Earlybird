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

//this scene will be loaded when user clicked the "start" menu
void GameScene::menuStartCallback(Object* pSender)
{
   // do something here
	float t = 2;
	
}