#include "MenuScene.h"

MenuScene::MenuScene(){}

MenuScene::~MenuScene(){}

bool MenuScene::init(){
	if(Scene::init()){
		return true;
	}else {
		return false;
	}
}

MenuLayer::MenuLayer(){}

MenuLayer::~MenuLayer(){}

bool MenuLayer::init(){
	if(Layer::init()) {
		return true;
	}else {
		return false;
	}
}