#pragma once

#include "cocos2d.h"
#include "AtlasLoader.h"

using namespace cocos2d;
using namespace std;

typedef enum _gravity {
	GRAVITY_CENTER = 1,
	GRAVITY_LEFT,
	GRAVITY_RIGHT
} Gravity;

/**
* The distance between two number
*/
const int NumberInterval = 4;

class NumberSeries : public Object{
public:
    NumberSeries();
    
    ~NumberSeries();
    
    virtual bool init();
    
    CREATE_FUNC(NumberSeries);
    
    void loadNumber(const char *fmt, int base = 0);
    
    SpriteFrame* at(int index);
private:
    Vector<SpriteFrame*> numberSeries;
};

/**
* @class Number
* Used to create the number sprite from texture and image, and
* give some useful support
*/
class Number{
public:
	/**
	* Default constructor
	*/
	Number();
	
	/**
	* Default destructor
	*/
	~Number();

	static Number* getInstance();

	static void destroyInstance();

	/**
	* cocos2d constructor
	*
	* @var fmt The file name like 'number_score_%2d', constructor will get number_score_00
	* to number_score_09 present the number 0 to 9
	*
	* @var base If the serious file name is not start with 0, you can set base to fix it
	*
	* #return instnce of number
	*/
	bool virtual loadNumber(const char* name, const char *fmt, int base = 0);

	/**
	* convert the integer number to Sprite present the number
	*
	* @var number The given number such as 4562
	*
	* @return the Node presenting the given number
	*/
	Node* convert(const char* name, int number, Gravity gravity = Gravity::GRAVITY_CENTER);

	virtual bool init();

private:
	Map<string, NumberSeries*> numberContainer;

	static Number* sharedNumber;
};