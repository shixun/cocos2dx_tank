//
//  ChoiceScene.h
//  TankProject
//
//  Created by yyb on 14-1-10.
//
//

#ifndef __TankProject__ChoiceScene__
#define __TankProject__ChoiceScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class ChoiceScene: public CCLayer {
    
public:
    // ChoiceScene();
    virtual bool init();
    CREATE_FUNC(ChoiceScene);
    static CCScene *scene();
    
    virtual void keyBackClicked(void);
    virtual void keyMenuClicked(void);
    
    void touchDownAction(CCObject* sender , unsigned int controlEvent);
    
private:
    int mRound = 1;
    void update();
};

#endif /* defined(__TankProject__ChoiceScene__) */
