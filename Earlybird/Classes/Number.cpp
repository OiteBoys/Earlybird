#include "Number.h"


Number* Number::sharedNumber = nullptr;

Number* Number::getInstance(){
	if(sharedNumber == NULL) {
		sharedNumber = new Number();
		if(!sharedNumber->init()){
			delete sharedNumber;
			sharedNumber = NULL;
			CCLOG("ERROR: Could not init sharedNumber");
		}
	}
	return sharedNumber;
}


void Number::destroyInstance()
{
    CC_SAFE_DELETE(sharedNumber);
}

bool Number::init(){
	return true;
}

Number::Number(){
}


Number::~Number(){
}


bool Number::loadNumber(const char* name, const char *fmt, int base){
	auto numbers = new Sprite*[10];
	for (int i = base; i < 10 + base; i++){
		const char *filename = String::createWithFormat(fmt, i)->getCString();
		auto frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		auto numberSprite = Sprite::createWithSpriteFrame(frame);
		numberSprite->setTag(i);
		numbers[i] = numberSprite;
	}
	numberContainer.insert(name, numbers);
	return true;
}


Node* Number::convert(const char* name, int number) {
	auto numbers = numberContainer.at(name);
	if (number == 0) {
		return numbers[0];
	}

	auto numberNode = Node::create();
	float totalWidth = 0;
	while(number){
		int temp = number % 10;
		number /= 10;
		auto sprite = numbers[temp];
		totalWidth += sprite->getContentSize().width;
		numberNode->addChild(sprite);
	}

	float singleWidth = totalWidth/numberNode->getChildrenCount();
	int index = numberNode->getChildrenCount()/2;
	for(auto child : numberNode->getChildren()) {
		index --;
		float offLength = singleWidth*index;
		child->setPositionX(offLength);
	}
	return numberNode;
}