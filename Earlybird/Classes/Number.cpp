#include "Number.h"

NumberSeries::NumberSeries(){}

NumberSeries::~NumberSeries(){}

bool NumberSeries::init() {
    this->numberSeries = Vector<SpriteFrame*>(10);
    return true;
}

void NumberSeries::loadNumber(const char *fmt, int base) {
    for (int i = base; i < 10 + base; i++){
		const char *filename = String::createWithFormat(fmt, i)->getCString();
		auto frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		numberSeries.pushBack(frame);
	}
}

SpriteFrame* NumberSeries::at(int index) {
    return this->numberSeries.at(index);
}

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
    auto numberSeries = NumberSeries::create();
    numberSeries->loadNumber(fmt, base);
	numberContainer.insert(name, numberSeries);
	return true;
}


Node* Number::convert(const char* name, int number) {
	auto numbers = numberContainer.at(name);
	if (number == 0) {
		return Sprite::createWithSpriteFrame(numbers->at(0));
	}

	auto numberNode = Node::create();
	float totalWidth = 0;
	while(number){
		int temp = number % 10;
		number /= 10;
		auto sprite = Sprite::createWithSpriteFrame(numbers->at(temp));
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