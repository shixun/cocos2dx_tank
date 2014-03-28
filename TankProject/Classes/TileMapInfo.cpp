//
//  TileMapInfo.cpp
//  TankProject
//
//  Created by yyb on 14-1-13.
//
//

#include "TileMapInfo.h"

void TileMapInfo::initMapInfoWithFile(const char *tmxFile) {
    
    
    mTMXTileMap = CCTMXTiledMap::create(tmxFile);
    
    mTMXLayers[0] = mTMXTileMap->layerNamed("layer_0");
    mTMXLayers[1] = mTMXTileMap->layerNamed("layer_1");
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize(); 
    CCSize mapSize = mTMXTileMap->getContentSize();
    CCSize tileSize = mTMXTileMap->getTileSize();
    
    printf("orMapSize: %f,%f\n",mapSize.width,mapSize.height);
    printf("orTileSize: %f,%f\n",tileSize.width,tileSize.height);
    
    printf("ddd,%f\n",winSize.height / mTMXTileMap->getContentSize().height);
    
    mTMXTileMap->setScale(winSize.height / mTMXTileMap->getContentSize().height);
    //将地图放到屏幕中间     锚点
    mTMXTileMap->setPosition(ccp((winSize.width - mapSize.width * mTMXTileMap->getScale()) / 2,
                                 (winSize.height - mapSize.height * mTMXTileMap->getScale()) / 2));
    
}

TileMapInfo* TileMapInfo::createMapInfoWithFile(const char *tmxFile) {
    
    
    TileMapInfo* tileMapInfo = new TileMapInfo();
    tileMapInfo->initMapInfoWithFile(tmxFile);
    
    return tileMapInfo;
}

// 边界碰撞检测
bool TileMapInfo::collisionTest(CCRect rect) {
    
    int gid = 0;
    CCSize mapSize = mTMXTileMap->getContentSize();  //地图的逻辑大小
    CCSize tileSize = mTMXTileMap->getTileSize();    // 地图的基本元的大小
    
    if(rect.getMinX() <0 || rect.getMaxX() >= mapSize.width
       || rect.getMinY() < 0 || rect.getMaxY() >= mapSize.height
       ) {
        return true;
    }
    
    /*
    for(int i=0;i<26;i++) {
        for(int j=0;j<26;j++) {
          int gid = mTMXLayers[0]->tileGIDAt(ccp(i,j));
            enumTileType type = gidToTileType[gid];
            int flag = 0;
            switch ((type)) {
                case tileNone:
                    flag = 0;
                    break;
                case tileGrass:
                    flag = 1;
                    break;
                case tileSteel:
                    flag = 2;
                    break;
                case tileWall:
                    flag = 3;
                    break;
                case tileRiver:
                    flag = 4;
                    break;
                case tileKing:
                    flag = 5;
                    break;
                default:
                    break;
            }
            printf("%d,",flag);
        }
    }
    */
    //将坦克Y坐标转换为地图上的Y坐标
    float MinY = mapSize.height - rect.getMinY();   //底边的y坐标
    float MaxY = mapSize.height - rect.getMaxY();   //顶边的y坐标
    
    //对坦克四个顶点进行碰撞检测
    gid = mTMXLayers[0]->tileGIDAt(ccp((int)(rect.getMinX() / tileSize.width),
                                       (int)(MinY / tileSize.height)));
    if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
        return true;
    gid = mTMXLayers[0]->tileGIDAt(ccp((int)(rect.getMinX() / tileSize.width),
                                       (int)(MaxY / tileSize.height)));
    if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
        return true;
    gid = mTMXLayers[0]->tileGIDAt(ccp((int)(rect.getMaxX() / tileSize.width),
                                       (int)(MaxY / tileSize.height)));
    if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
        return true;
    gid = mTMXLayers[0]->tileGIDAt(ccp((int)(rect.getMaxX() / tileSize.width),
                                       (int)(MinY / tileSize.height)));
    if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass)
        return true;
    
    return false;
}






