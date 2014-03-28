//
//  CityScene.h
//  TankProject
//
//  Created by yyb on 14-1-10.
//
//

#ifndef __TankProject__CityScene__
#define __TankProject__CityScene__

#include <iostream>
#include "cocos2d.h"
#include "Tank.h"
#include "Panel.h"
#include "EnemyAI.h"
using namespace cocos2d;

class CityScene :public cocos2d::CCLayer {
    
public:
    
    virtual bool init();
    
    static CCScene *scene();
    static CCScene *scene(int round);
    CREATE_FUNC(CityScene);
    static CityScene *create(int round);
    virtual void onEnter();
    virtual void update(float delta);    
    
    
    CC_SYNTHESIZE(int ,m_nRound, Round);
    

    
    Tank*  mPlayerTank[2];
    Panel* myPanel;
    EnemyAI* mEnemyAI;
};


#endif /* defined(__TankProject__CityScene__) */
