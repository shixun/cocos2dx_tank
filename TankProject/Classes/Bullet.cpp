//
//  Bullet.cpp
//  TankProject
//
//  Created by yyb on 14-1-13.
//
//

#include "Bullet.h"


void Bullet::initBulletWithTank(Tank *tank) {
    
    
    mTank = tank;
    mTileMapInfo = mTank->getTileMapInfo();
    initWithSpriteFrameName("bullet.png");
    mTileMapInfo->getTileMap()->addChild(this);
    setVisible(false);
}

Bullet* Bullet::createBulletWithTank(Tank *tank) {
    
    Bullet* bullet = new Bullet();
    bullet->initBulletWithTank(tank);
    bullet->autorelease();
    return bullet;
}

bool Bullet::fire()
{
    
    if(!mFlyState)
    {
        
        mFlyState = true;
        setVisible(true);
        setPosition(mTank->getPosition()); 
         //设置子弹运行方向
        int Rotation = mTank->getRotation();
        switch (Rotation)
        {
            case 0:
                stepX = 0.0f, stepY = 2.0f;
                break;
            case 90:
                stepX = 2.0f, stepY = 0.0f;
                break;
            case 180:
                stepX = 0.0f, stepY = -2.0f;
                break;
            case 270:
                stepX = -2.0f, stepY = 0.0f;
                break;
            default:
                break;
        }  
        scheduleUpdate();
        return true;
    }
    
    return false;
}

    
    
void Bullet::update(float delta) {
    
     CCSprite::update(delta);
    //设置移动后的位置
    mMovedRect = boundingBox();
	mMovedRect.origin.x += stepX;
	mMovedRect.origin.y += stepY;
    setPosition(ccp(getPositionX() + stepX, getPositionY() + stepY));
     //检测是否有碰撞
     CCRect rect = boundingBox(); 
    if (mTileMapInfo->collisionTest(rect))
    {
        //unscheduleUpdate();
        //setVisible(false);
        // isFlying = false;
        
        stopFire();
        
        //引爆子弹
        bulletBoom();
    }
    
}


void Bullet::bulletBoom() {
    
     CCRect rect = boundingBox(); 
     CCSize mapSize = mTileMapInfo->getTileMap()->getContentSize();
    
    if (rect.getMinX() < 0 || rect.getMaxX() >= mapSize.width ||
        rect.getMinY() < 0 || rect.getMaxY() >= mapSize.height)
        return ;
    
    CCTMXLayer* tmxLayer = mTileMapInfo->getTileMap()->layerNamed("layer_0"); 
    CCSize tileSize = tmxLayer->getMapTileSize(); 
    
    //调整Y轴位tmx地图中的Y轴
     float MinY = mapSize.height - rect.getMinY();  
     float MaxY = mapSize.height - rect.getMaxY();
    
    //将与子弹碰撞的墙壁tileWall图块删除
    CCPoint pt = ccp((int)rect.getMinX() / tileSize.width,(int)(MinY / tileSize.height)); 
    if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
        tmxLayer->setTileGID(gidToTileType[tileNone], pt);
    pt = ccp((int)rect.getMinX() / tileSize.width,(int)(MaxY / tileSize.height));  
    
    if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
        tmxLayer->setTileGID(gidToTileType[tileNone], pt);
     pt = ccp((int)rect.getMaxX() / tileSize.width,(int)(MinY / tileSize.height));  
    
    if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
        tmxLayer->setTileGID(gidToTileType[tileNone], pt);
     pt = ccp((int)rect.getMaxX() / tileSize.width,(int)(MaxY / tileSize.height)); 
    
    if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
        tmxLayer->setTileGID(gidToTileType[tileNone], pt);
    
}

bool Bullet::stopFire() {
    
    if(mFlyState == true) {
        
        mFlyState = false;
        setVisible(false);
        unscheduleUpdate();
        return true;
        
    }
    
    return false;
    
}

