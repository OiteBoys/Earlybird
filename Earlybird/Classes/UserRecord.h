#pragma once
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class UserRecord : public Object
{
public:
	UserRecord();
	~UserRecord();

	static UserRecord* getInstance();

	static void destroyInstance();

	virtual bool init();
	/**
	 * @var key : the key that point the the data which will be sotred
	 *
	 * @var data: the data will be stored
	 *
	 * as a matter of fact, the score will be stored in local memory with XML format.
	 */
	void saveIntegerToUserDefault(const char* key, int score);

	/*
	 * @var key: get the data with the key we used to stored it.
	 *
	 * @return the data we have been stored, with the attached key
	 */
	int readIntegerFromUserDefault(const char* key);

private:
	static UserRecord* shareUserRecord;
};
