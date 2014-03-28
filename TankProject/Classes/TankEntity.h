//
//  TankEntity.h
//  TankProject
//
//  Created by yyb on 14-3-18.
//
//

#ifndef __TankProject__TankEntity__
#define __TankProject__TankEntity__

#include <iostream>
#include "Entity.h"
#include "TileMapInfo.h"

class TankEntity:public Entity {
    
public:
    TankEntity();
    ~TankEntity();
    CREATE_FUNC(TankEntity);
    virtual bool init();
    static TankEntity* createTankWithTankType(const char* tankTypeName, TileMapInfo* tileMapInfo);
    void initTankWithTankType(const char* tankTypeName, TileMapInfo* tileMapInfo);
    void move(float x,float y);
    void remove();
    // void moveEnd();
    void update(float delta);
    void setTankType(CCString* tankType);
    CCString* getTankType();
    void setUserId(int userId);
    int getUserId();
    void setEntityId(int entityId);
    int getEntityId();
    void initTankFrame();
    void setIsCache();
    bool getIsCache();
    

private:

     CC_SYNTHESIZE(TileMapInfo*, mTileMapInfo, TileMapInfo);
     CC_SYNTHESIZE(CCRect, mMovedRect, MovedRect);
     CC_SYNTHESIZE(bool, IsBlock, Block);
     //CC_SYNTHESIZE(bool,isCache, Cache);
     CCString* tankType;
     int userId;
     int entityId;
     bool isCache = false;
     

};



#endif /* defined(__TankProject__TankEntity__) */

