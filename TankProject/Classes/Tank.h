//
//  Tank.h
//  TankProject
//
//  Created by yyb on 14-1-10.
//
//

#ifndef __TankProject__Tank__
#define __TankProject__Tank__

#include <iostream>
#include "cocos2d.h"
#include "Panel.h"
#include "TileMapInfo.h"
#include "CommonValue.h"
using namespace cocos2d;
class Bullet;
class Tank: public CCSprite {
    
public:
    
    static Tank* createTankWithTankType(const char* tankTypeName, TileMapInfo* tileMapInfo);
    void initTankWithTankType(const char* tankTypeName, TileMapInfo* tileMapInfo);
    bool command(enumOrder order);
    // TileMapInfo* mTileMapInfo;
    void remove();
    void move();
    CCString* getUserId();
    void setUserId(CCString* userId);
    
    //void setBlock(bool isBlock);
    //bool getBlock();
    
private:
    //bool mIsBlock;
    CCString* userId;
    CC_SYNTHESIZE(Bullet*, mBullet, Bullet);
	CC_SYNTHESIZE(TileMapInfo*, mTileMapInfo, TileMapInfo);
	CC_SYNTHESIZE(float, mBulletDelta, BulletDelta);
	CC_SYNTHESIZE(enumObjectType, mObjType, ObjType);
	CC_SYNTHESIZE(CCRect, mMovedRect, MovedRect);
    CC_SYNTHESIZE(bool, IsBlock, Block);
};



#endif /* defined(__TankProject__Tank__) */
