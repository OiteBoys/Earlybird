//
//  OptionLayer.h
//  parasite-city
//
//  Created by Zhou.Zeyong on 14-2-18.
//
//

#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class OptionDelegate
{
public:
    virtual void onTouch() = 0;
};

class OptionLayer:public Layer
{
public:
    OptionLayer();
    ~OptionLayer();
    
    virtual bool init();
    CREATE_FUNC(OptionLayer);
    
    // override
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    
    CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};