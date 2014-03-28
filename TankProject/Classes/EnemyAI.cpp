//
//  EnemyAI.cpp
//  TankProject
//
//  Created by yyb on 14-1-13.
//
//

#include "EnemyAI.h"
#include "Bullet.h"

void EnemyAI::initEnemyAIWithTank(Tank *tank) {
    
    mTank = tank;
    mTileMapInfo = tank->getTileMapInfo();
    mEnemyTanks = CCArray::createWithCapacity(4);
    mEnemyTanks->retain();
    
    //初始化出现地点
     CCSize mapSize = mTileMapInfo->getTileMap()->getContentSize();  
    CCSize tileSize = mTileMapInfo->getTileMap()->layerNamed("layer_0")->getMapTileSize(); 
 
    bornPoint[0] = ccp(tileSize.width, mapSize.height - tileSize.height);  
    bornPoint[1] = ccp(mapSize.width / 2, mapSize.height - tileSize.height);
    bornPoint[2] = ccp(mapSize.width - tileSize.width, mapSize.height - tileSize.height); 
    
}


EnemyAI*  EnemyAI::createEnemyAIWithTank(Tank *tank) {
    
    EnemyAI* enemyTank = new EnemyAI();
    enemyTank->initEnemyAIWithTank(tank);
    
    return enemyTank;
    
}

void EnemyAI::addTank(float delta) {
    
    static float deltaTimes = 0.0f;
    deltaTimes += delta;
    if(deltaTimes >= 2.0f) {
        
        deltaTimes = 0.0f;
        int count = mEnemyTanks->count();
       
        if (count < 3)   //先从固定位置添加三个坦克
        {
            Tank* enemyTank = Tank::createTankWithTankType(enemyTankType[count], mTileMapInfo);
            enemyTank->setPosition(bornPoint[count]);
            enemyTank->setRotation(180.0f);
            mEnemyTanks->addObject(enemyTank);
        }else if(count == 3) {
            
            int tankTypeIndex = (int)(CCRANDOM_0_1() * 4) % 3;
            Tank* enemyTank = Tank::createTankWithTankType(enemyTankType[tankTypeIndex], mTileMapInfo);
            enemyTank->setPosition(bornPoint[tankTypeIndex]);
            enemyTank->setRotation(180.0f);
            mEnemyTanks->addObject(enemyTank);
        }
        
    }
    
    
    
}


void EnemyAI::tankAction(float delta) {
    
    CCObject* pObj;
    
    // int nCount = 0;
    CCARRAY_FOREACH(mEnemyTanks, pObj){
        
        Tank* tank = (Tank*)pObj;
        
        //坦克自动移动，碰到墙壁自动换方向  
        int Rotation = tank->getRotation();
       //  printf("this:com:%d",Rotation);
        // 须要修改
      //    printf("com:%d\n",Rotation / 90 + 1);
        
        tank->command((enumOrder)(Rotation / 90 + 1));
        
        /*
        if(nCount == 0) {
            printf("com:%d\n",Rotation / 90 + 1);
             printf("ro:%d\n",Rotation);
        }
        nCount++;
        */
        //printf("%d\n",Rotation / 90 + 1);
        
        /*
        if (!tank->command((enumOrder)(Rotation / 90 + 1)))
        {
            int n = (int)(CCRANDOM_0_1() * 5) % 5;
            if (n != 0)
                tank->command((enumOrder)n);
        }
        */
        
        //每隔一秒开一次火 
        tank->setBulletDelta(tank->getBulletDelta()+ delta);
        if (tank->getBulletDelta() > 1)
        {
            //开火后，如果子弹在飞行中，归零计时
            if (tank->command(cmdFire))
            {
                tank->setBulletDelta(0.0);
            }
        }
        
        //检测坦克之间的碰撞
        
        
        
        //如果坦克阻塞，换个方向
        
        /*
        f (tank->getBlock())
            tank->setRotation((int)(CCRANDOM_0_1() * 3.2) * 90);
         */
        
        //如果上面的判断完成后，坦克根据自己的阻塞状态移动
        
         // tank->move();
        
        
    }
    
    collisionTest();
    move();
     //  mTank->move();
    
    
}

void EnemyAI::move() {
    
    mTank->move();
    CCObject* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Tank* tank = (Tank*)pObj;
        //如果坦克阻塞，换个方向
        if (tank->getBlock())
            tank->setRotation((int)(CCRANDOM_0_1() * 3.8) * 90);
        //如果上面的判断完成后，坦克根据自己的阻塞状态移动
        tank->move();
    }
    
    
    
}



void EnemyAI::update(float delta) {
    addTank(delta);
    tankAction(delta);
}

bool EnemyAI::IsRectIntersect(CCRect rectA, CCRect rectB) {
    
    float left = fmax(rectA.getMinX(), rectB.getMinX()); 
    float right = fmin(rectA.getMaxX(), rectB.getMaxX());
    
    if (left > right)
        return false;
   
     float top = fmin(rectA.getMaxY(), rectB.getMaxY());
     float bottom = fmax(rectA.getMinY(), rectB.getMinY()); 
    
    if (top < bottom)
        return false;
    
    return true;
    
}

void EnemyAI::collisionTest() {
    
    
    /*
    //坦克和敌方坦克之间的碰撞检测     
     CCObject* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Tank* enemyTank = (Tank*)pObj;
        if (IsRectIntersect(mTank->getMovedRect(), enemyTank->getMovedRect()))
        {
            enemyTank->setBlock(true);
            mTank->setBlock(true);
        }
    }
    
    //敌方坦克之间的碰撞
     CCArray* ccTmpArray = CCArray::create();
     ccTmpArray->addObjectsFromArray(mEnemyTanks);
    
    while (ccTmpArray->count())
    {
        CCObject* pObj;
        Tank* tmpTank = (Tank*)ccTmpArray->lastObject();
        ccTmpArray->removeLastObject();
        CCARRAY_FOREACH(ccTmpArray, pObj)
        {
            if (IsRectIntersect(tmpTank->getMovedRect(),
                                ((Tank*)pObj)->getMovedRect()))
            {
                tmpTank->setBlock(true);
                ((Tank*)pObj)->setBlock(true);
                ccTmpArray->removeObject(pObj);
            }
        }
    }
    */
    
    
    // 坦克之间的碰撞
    Bullet* playerBullet = mTank->getBullet();
    CCArray* ccTmpArray = CCArray::create();
    ccTmpArray->addObjectsFromArray(mEnemyTanks);
    ccTmpArray->addObject(mTank);
    CCObject* pObjSrc;
    CCARRAY_FOREACH(ccTmpArray, pObjSrc)
    {
        Tank* tankSrc = (Tank*)pObjSrc;
        CCObject* pObjdst;
        CCARRAY_FOREACH(ccTmpArray, pObjdst)
        {
            Tank* tankDst = (Tank*)pObjdst;
            if (tankSrc != tankDst)
            {
                CCRect rectDst;
                if (ccTmpArray->indexOfObject(pObjSrc) > ccTmpArray->indexOfObject(pObjdst))
                {
                    //之前的坦克已经确定了要移动的位置
                    rectDst = tankDst->getMovedRect();
                }
                else
                {
                    //还没有确定要移动的坦克
                    rectDst = tankDst->boundingBox();
                }
                if (IsRectIntersect(tankSrc->getMovedRect(), rectDst))
                {
                    //确保在移动之前没有重合
                    if (!IsRectIntersect(tankSrc->boundingBox(), rectDst))
                    {
                        tankSrc->setBlock(true);
                    }
                }
            }
        }
    }
    
    //玩家子弹和敌方子弹之间的碰撞
    CCObject* pObj;
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Bullet* enemyBullet = ((Tank*)pObj)->getBullet();
        if (playerBullet->getFlyState() && enemyBullet->getFlyState())
        {
            if (IsRectIntersect(playerBullet->getMovedRect(), enemyBullet->getMovedRect()))
            {
                enemyBullet->stopFire();
                playerBullet->stopFire();
                break;
            }
           
        }
    }
    
    //玩家子弹和敌方坦克的碰撞
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        if (playerBullet->getFlyState())
        {
            Tank* enemyTank = (Tank*)pObj;
            if (IsRectIntersect(playerBullet->getMovedRect(), enemyTank->getMovedRect()))
            {
                mEnemyTanks->removeObject(pObj);
                enemyTank->remove();
                playerBullet->stopFire();
                // printf("inininininininininininini");
                break;
            }
        }
    }
    
    //敌人子弹和玩家的碰撞
    CCARRAY_FOREACH(mEnemyTanks, pObj)
    {
        Bullet* enemyBullet = ((Tank*)pObj)->getBullet();
        if (enemyBullet->getFlyState())
        {
            if (IsRectIntersect(enemyBullet->getMovedRect(), mTank->getMovedRect()))
            {
                mTank->setVisible(false);
                enemyBullet->stopFire();
                // printf("outoutout");
                break;
            }
        }
    }
    
    //子弹和大本营之间的碰撞
    
    
}



