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
	return true;
}

void AtlasLoader::loadAtlas(string filename){
	auto textureAtlas = Director::getInstance()->getTextureCache()->addImage("atlas.png");
	this->loadAtlas(filename, textureAtlas);
}

void AtlasLoader::loadAtlas(string filename, Texture2D *texture) {
	string data = FileUtils::getInstance()->getStringFromFile(filename);
	unsigned pos;Atlas atlas;
	pos = data.find_first_of("\n");
	string line = data.substr(0, pos);
	data = data.substr(pos + 1);
	while(line != ""){
		sscanf(line.c_str(), "%s %d %d %f %f %f %f", 
		atlas.name, &atlas.width, &atlas.height, &atlas.start.x, 
		&atlas.start.y, &atlas.end.x, &atlas.end.y);
		atlas.start.x = 1024*atlas.start.x;
		atlas.start.y = 1024*atlas.start.y;
		atlas.end.x = 1024*atlas.end.x;
		atlas.end.y = 1024*atlas.end.y;

		pos = data.find_first_of("\n");
		line = data.substr(0, pos);
		data = data.substr(pos + 1);

		// use the data to create a sprite frame
        // fix 1px edge bug
        if(atlas.name == string("land")) {
            atlas.start.x += 1;
        }
		Rect rect = Rect(atlas.start.x, atlas.start.y, atlas.width, atlas.height);
		auto frame = SpriteFrame::createWithTexture(texture, rect);
		this->_spriteFrames.insert(string(atlas.name), frame);
	}
}

SpriteFrame* AtlasLoader::getSpriteFrameByName(string name){
	return this->_spriteFrames.at(name);
}
