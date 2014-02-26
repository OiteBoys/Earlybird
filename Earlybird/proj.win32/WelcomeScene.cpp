#include "WelcomeScene.h"

WelcomeScene::WelcomeScene(){};

WelcomeScene::~WelcomeScene(){};

bool WelcomeScene::init(){
	if(Scene::init()){
		return true;
	}else{
		return false;
	}
}
