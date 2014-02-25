#pragma once
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

/**
* To see the single line in the file:
* bird0_1 48 48 0.0546875 0.9472656 0.046875 0.046875
*/
typedef struct _atlas{
	char name[255];
	int width;
	int height;
	Point start;
	Point end;
} Atlas;

class AtlasLoader{
public:
	/**
	*  Get the instance of AtlasLoader
	*/
	static AtlasLoader* getInstance();

	/**
     *  Destroys the instance of AtlasLoader.
     */
    static void destroyInstance();

protected:
	/**
     *  The default constructor.
     */
    AtlasLoader();
    
    /**
     *  Initializes the instance of FileUtils. It will set _searchPathArray and _searchResolutionsOrderArray to default values.
     *
     *  @note When you are porting Cocos2d-x to a new platform, you may need to take care of this method.
     *        You could assign a default value to _defaultResRootPath in the subclass of FileUtils(e.g. FileUtilsAndroid). Then invoke the FileUtils::init().
     *  @return true if successed, otherwise it returns false.
     *
     */
    virtual bool init();

	/**
	*   Load the atlas of file
	*/
	void loadAtlas();

	/**
	* Get the sprite by name.
	* Warm: you should use this function after add atlas.png to getTextureCache,
	* or this function will take you a long time to load texture.
	*/
	SpriteFrame* getSpriteFrameByName(string name);

	/**
     *  The singleton pointer of AtlasLoader.
     */
    static AtlasLoader* sharedAtlasLoader;

	/**
	*  The container that store all the atlas data form atlas.txt
	*/
	vector<Atlas> atlases;

	/**
	*  container to store all the sprite frame that already loaded;
	*/
	//Map<std::string, SpriteFrame*> _spriteFrames;
};