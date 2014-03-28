//
//  Tank.cpp
//  TankProject
//
//  Created by yyb on 14-1-10.
//
//

#include "Tank.h"
#include "Bullet.h"


Tank* Tank::createTankWithTankType(const char *tankTypeName, TileMapInfo* tileMapInfo) {
    
    
    CCSpriteFrameCache *pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile("tank.plist");
    
    Tank* tank = new Tank();
    //tank->initWithSpriteFrameName(tankTypeName);
    tank->initTankWithTankType(tankTypeName, tileMapInfo);
    tank->autorelease();
    
    return tank;
    
}






bool Tank::command(enumOrder order) {
    
    float stepX = 0.0f;
    float stepY = 0.0f;
    float fRotation = getRotation();
    
    
   // CCRect srect = this->boundingBox();
   // printf("SSSSSSrect_pos: %f, %f",srect.getMinX(),srect.getMinY());
    
   //  printf("fro:%lf\n",fRotation);
    //  printf("thisOrder:%d\n",order);
    
    // printf("coomd:%lf\n",fRotation);
    // printf("whatorder:%d\n",cmdGoDown);
    switch(order) {
            
        case cmdNothing:
        break;
        case cmdGoUP:
            stepY = 1.0f;
            fRotation = 0.0f;
            break;
        case cmdGoDown:
            stepY = -1.0f;
            fRotation = 180.0f;
            break;
        case cmdGoLeft:
            stepX = -1.0f;
            fRotation = 270.0f;
            break;
        case cmdGoRight:
            stepX = 1.0f;
            fRotation = 90.0f;
            break;
        case cmdFire:
           return  mBullet->fire();
            //  break;
        default:
            break;
            
    }
   
    //setPositionX(getPositionX() + stepX);
    //setPositionY(getPositionY() + stepY);
    setRotation(fRotation);
    
    CCRect rect = this->boundingBox();
    
    //printf("rect: %f,%f\n",rect.size.width,rect.size.height);
    printf("minx %f,  %f\n",rect.getMinX(),rect.getMinY());
    
    mMovedRect = CCRectMake(rect.getMinX() + stepX,
                            rect.getMinY() + stepY, rect.size.width, rect.size.height);
    if (!mTileMapInfo->collisionTest(mMovedRect))
	{
		IsBlock = false;
		return true;
	}
    
    mMovedRect = rect;
	IsBlock = true;
    
    
    /*
    if (!mTileMapInfo->collisionTest(CCRectMake(rect.getMinX() + stepX,
                                                rect.getMinY() + stepY, rect.size.width, rect.size.height)))
    {
        setPositionX(getPositionX() + stepX);
        setPositionY(getPositionY() + stepY);
        return true;  
    }
    */
    
    return false;
}


void Tank::initTankWithTankType(const char *tankTypeName, TileMapInfo *tileMapInfo) {
    
    initWithSpriteFrameName(tankTypeName);
    mTileMapInfo = tileMapInfo;
    
    mTileMapInfo->getTileMap()->addChild(this);
    CCTMXTiledMap* tmxTileMap = mTileMapInfo->getTileMap(); 
    CCSize tileSize = tmxTileMap->getTileSize();
    
    CCSize tankSize = getContentSize();
    
    printf("cont: %f,%f\n",tankSize.width,tankSize.height);
   // CCRect rect = this->boundingBox();
   //  printf("rect_pos: %f, %f",rect.getMinX(),rect.getMinY());
    
    setScale((tileSize.height * 2-4) / (tankSize.height));
    
    
    // CCRect rect = this->boundingBox();
    // printf("rect_pos: %f, %f",rect.getMinX(),rect.getMinY());
    
   mBullet = Bullet::createBulletWithTank(this);
}

void Tank::move() {
    
    if(!IsBlock) {
        setPosition(ccp(mMovedRect.getMidX(), mMovedRect.getMidY())); 
    }
    
    
}

/*
void Tank::setBlock(bool isBlock)
{
	mIsBlock = isBlock;
	if (mIsBlock == true)
	{
		mMovedRect = boundingBox();
	}
}

bool Tank::getBlock()
{
	return mIsBlock;
}
*/

void Tank::remove() {
    mTileMapInfo->getTileMap()->removeChild(this);
}



void Tank::setUserId(cocos2d::CCString *userId) {
    this->userId = userId;
}

CCString* Tank::getUserId() {
    return this->userId;
}







