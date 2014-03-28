//
//  TankEntity.cpp
//  TankProject
//
//  Created by yyb on 14-3-18.
//
//

#include "TankEntity.h"


TankEntity::TankEntity() {
    
}

TankEntity::~TankEntity() {
    
}

bool TankEntity::init() {
    return true;
}

TankEntity* TankEntity::createTankWithTankType(const char *tankTypeName, TileMapInfo *tileMapInfo) {
    
    CCSpriteFrameCache *pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile("tank.plist");
    
    TankEntity* tank = new TankEntity();
    if(!tank) {
        tank->init();
    }
    
    //tank->initWithSpriteFrameName(tankTypeName);
    tank->initTankWithTankType(tankTypeName, tileMapInfo);
    tank->autorelease();
    
    return tank;
    
}



void TankEntity::initTankWithTankType(const char *tankTypeName, TileMapInfo *tileMapInfo) {
    
    
        CCSpriteFrameCache *pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile("tank.plist");
    
    CCSprite* sprite = CCSprite::create();
    
    sprite->initWithSpriteFrameName(tankTypeName);
    this->bindSprite(sprite);
    
    // initWithSpriteFrameName(tankTypeName);
    mTileMapInfo = tileMapInfo;
    
    mTileMapInfo->getTileMap()->addChild(this);
    CCTMXTiledMap* tmxTileMap = mTileMapInfo->getTileMap();
    CCSize tileSize = tmxTileMap->getTileSize();
    
    CCSize tankSize = this->getSprite()->getContentSize();
    //CCSize size = this->getSprite()->getContentSize();
    //this->setContentSize(size);
    //CCSize tankSize = this->getContentSize();
    //getContentSize();
    //this->getSprite()->setScale((tileSize.height * 2-4) / (tankSize.height));
    // float fScale = (size.height*2-4) / (size.height);
    
   this->setScale((tileSize.height * 2-4) / (tankSize.height));
   // CCSize size = this->getSprite()->getContentSize();
   // this->setContentSize(size);
    
    //this->setScale(fScale);
    
    // this->setContentSize(CCSize(28, 28));
    
    // this->autorelease();
    
}

void TankEntity::move(float x, float y) {
    
   
    float stepX = 0.0f;
    float stepY = 0.0f;
     float fRotation = getRotation();
    
   // CCRect crect = this->boundingBox();
   // printf("crect: %f ,%f",crect.getMinX(),crect.getMinY());
      
    switch(this->getOrder()) {
        case ocmdGoUP:
            stepY = 1.0f;
            fRotation = 0.0f;
            break;
        case ocmdGoDown:
            stepY = -1.0f;
            fRotation = 180.0f;
            break;
        case ocmdGoRight:
            stepX = 1.0f;
            fRotation = 90.0f;
            break;
        case ocmdGoLeft:
            stepX = -1.0f;
            fRotation = 270.0f;
            break;
        default:
            break;
    }
    
    this->setRotation(fRotation);
    //CCRect rect = this->getSprite()->boundingBox();
    //// rect.
    CCRect rect = this->boundingBox();
    printf("rect_size:%f , %f\n",rect.size.width,rect.size.height);
    
     printf("rect %f,  %f\n",rect.getMinX(),rect.getMinY());
       
    
    mMovedRect = CCRectMake(rect.getMinX() + stepX-TANKTILESIZE,
                            rect.getMinY() + stepY-TANKTILESIZE, TANKTILESIZE*2, TANKTILESIZE*2);
    
    if (!mTileMapInfo->collisionTest(mMovedRect))
	{
		IsBlock = false;
		return;
	}
  //   CCLOG("ssssssssss");
    
    this->setXY(this->getPositionX()-stepX, this->getPositionY()-stepY);
    mMovedRect = rect;
    IsBlock = true;
    
    
    
    //CCMoveBy* moveBy = NULL;
       /*
    if(moveBy == NULL) {
        return;
    }
    
    //CCMoveTo* moveTo = CCMoveTo::create(0.9f,ccp(100,100));
    CCCallFunc*  callFunc = CCCallFunc::create(this, callfunc_selector(TankEntity::moveEnd));
    
    CCActionInterval* moveActions = CCSequence::create(moveBy,callFunc,NULL);
    this->runAction(moveActions);
     */
}


void TankEntity::remove() {
    mTileMapInfo->getTileMap()->removeChild(this);

}

/*
void TankEntity::moveEnd() {
    this->setOrder(cmdNothing);
}
*/


void TankEntity::update(float delta) {
    
    if(this->getOrder() != ocmdNothing && IsBlock == false
       && this->getOrder()!= ocmdBorn && this->getOrder() !=ocmdFire ) {
        
        this->setPosition(ccp(mMovedRect.getMidX(), mMovedRect.getMidY()));
        this->setOrder(ocmdNothing);
    }
    if(this->getOrder() == ocmdBorn) {
        CCLOG("born   born  born!");
        this->setPosition(this->getPosx(),this->getPosy());
        this->setOrder(ocmdNothing);
    }
       
}



void TankEntity::setTankType(cocos2d::CCString *tankType) {
    this->tankType = tankType;
}

CCString* TankEntity::getTankType() {
    return this->tankType;
}

void TankEntity::setUserId(int userId) {
    this->userId = userId;
}

int TankEntity::getUserId() {
    return this->userId;
}

int TankEntity::getEntityId() {
    return this->entityId;
}


void TankEntity::setEntityId(int entityId) {
    this->entityId = entityId;
}


void TankEntity::initTankFrame() {
    
    CCSpriteFrameCache *pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile("tank.plist");
    isCache = true;
    
}

void TankEntity::setIsCache() {
    // CCBool = CCBool.bool;
    isCache = !isCache;
}

bool TankEntity::getIsCache() {
    return isCache;
}

