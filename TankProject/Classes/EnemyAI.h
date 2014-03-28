//
//  EnemyAI.h
//  TankProject
//
//  Created by yyb on 14-1-13.
//
//

#ifndef __TankProject__EnemyAI__
#define __TankProject__EnemyAI__

#include <iostream>
#include "cocos2d.h"
#include "Tank.h"
using namespace cocos2d;


static const char* enemyTankType[] =
{
  "normalU.png","speedU.png","armor1U.png"  
};

class EnemyAI {
    
public:
    static EnemyAI* createEnemyAIWithTank(Tank* tank); 
    void initEnemyAIWithTank(Tank* tank); 
    void update(float delta);
    
    void collisionTest();
    bool IsRectIntersect(CCRect rectA, CCRect rectB);
    
private:
    void addTank(float delta);
    void tankAction(float delta);
    void move();
    
private:
    CCArray* mEnemyTanks;
    Tank* mTank;
    TileMapInfo* mTileMapInfo;
    
     //出现地点
     CCPoint bornPoint[3]; 
    
};



#endif /* defined(__TankProject__EnemyAI__) */
