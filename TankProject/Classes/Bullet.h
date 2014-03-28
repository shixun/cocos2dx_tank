//
//  Bullet.h
//  TankProject
//
//  Created by yyb on 14-1-13.
//
//

#ifndef __TankProject__Bullet__
#define __TankProject__Bullet__

#include <iostream>
#include "cocos2d.h"
#include "Tank.h"
using namespace cocos2d;

class Bullet : public CCSprite {
    
public:
    
    static Bullet* createBulletWithTank(Tank* tank);
    void initBulletWithTank(Tank* tank);
    bool fire();
    virtual void update(float delta);
    void bulletBoom();
    bool stopFire();
    
private:
    bool isFlying = false;
    Tank* mTank;
    TileMapInfo* mTileMapInfo;
    float stepX,stepY;
    
    CC_SYNTHESIZE(CCRect, mMovedRect, MovedRect);
	CC_SYNTHESIZE(bool, IsBlock, Block);
	//CC_SYNTHESIZE(bool, mFlyState, FlyState);
    CC_SYNTHESIZE(bool,mFlyState,FlyState);
};


#endif /* defined(__TankProject__Bullet__) */
