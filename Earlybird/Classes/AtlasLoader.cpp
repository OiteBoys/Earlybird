#include "AtlasLoader.h"

AtlasLoader* AtlasLoader::sharedAtlasLoader = nullptr;

AtlasLoader* AtlasLoader::getInstance(){
	if(sharedAtlasLoader == NULL) {
		sharedAtlasLoader = new AtlasLoader();
		if(!sharedAtlasLoader->init()){
			delete sharedAtlasLoader;
			sharedAtlasLoader = NULL;
			CCLOG("ERROR: Could not init sharedAtlasLoader");
		}
	}
	return sharedAtlasLoader;
}


void AtlasLoader::destroyInstance()
{
    CC_SAFE_DELETE(sharedAtlasLoader);
}

AtlasLoader::AtlasLoader(){}


bool AtlasLoader::init(){
	this->atlases = new vector<Atlas>(71);
	return true;
}

void AtlasLoader::loadAtlas(){
	string data = FileUtils::getInstance()->getStringFromFile("atlas.txt");
	unsigned pos;Atlas atlas;
	pos = data.find_first_of("\n");
	string line = data.substr(0, pos);
	data = data.substr(pos + 1);
	while(line != ""){
		sscanf(line.c_str(), "%s %d %d %f %f %f %f %f", 
		atlas.name, &atlas.width, &atlas.height, &atlas.start.x, 
		&atlas.start.y, &atlas.end.x, &atlas.end.y);
		atlas.start.x = 1024*atlas.start.x;
		atlas.start.y = 1024*atlas.start.y;
		atlas.end.x = 1024*atlas.end.x;
		atlas.end.y = 1024*atlas.end.y;
		this->atlases.push_back(atlas);

		pos = data.find_first_of("\n");
		line = data.substr(0, pos);
		data = data.substr(pos + 1);
	}
}

SpriteFrame* AtlasLoader::getSpriteFrameByName(string name){
	for (auto atlas : atlases){
		if(name == atlas.name) {
			//auto textureAtlas = Director::getInstance()->getTextureCache()->getTextureForKey("atlas.png");
			auto textureAtlas = Director::getInstance()->getTextureCache()->addImage("atlas.png");
			Rect rect = Rect(atlas.start.x, atlas.start.y, atlas.width, atlas.height);
			auto frame = SpriteFrame::createWithTexture(textureAtlas, rect);
			return frame;
		}
	}
	return nullptr;
}