//
//  CityScene.cpp
//  TankProject
//
//  Created by yyb on 14-1-10.
//
//

#include "CityScene.h"


CCScene* CityScene::scene() {
    
    CCScene* scene = CCScene::create();
    
    CityScene* layer = CityScene::create();
    
    scene->addChild(layer);
    
    return scene;
}


CCScene* CityScene::scene(int round) {
    
    CCScene* scene = CCScene::create();
    CityScene* layer = CityScene::create(round);
    scene->addChild(layer);       
     return scene;
}


CityScene* CityScene::create(int round) {
    
    
    CityScene* pRet = new CityScene();
    if(pRet) {
        
        pRet->setRound(round);
        if(pRet->init()) {
            
            pRet->autorelease();
            return pRet;
        }
        
    }
    
    
    return NULL;
}

bool CityScene::init() {
    
    CCLayer::init();
    
    
    // 初始化地图信息
     TileMapInfo* tileMapInfo = TileMapInfo::createMapInfoWithFile("Round5.tmx"); 
     CCTMXTiledMap* tmxTileMap = tileMapInfo->getTileMap();  
    this->addChild(tmxTileMap);  
    
    //在已有的地图上，创建玩家坦克
    mPlayerTank[0] = Tank::createTankWithTankType("player2U.png", tileMapInfo);
    
     //放到地图中初始化位置  
      CCSize tileSize = tmxTileMap->getTileSize();  
      CCSize mapSize = tmxTileMap->getContentSize();
      mPlayerTank[0]->setPosition(ccp(mapSize.width / 2 - tileSize.width * 3, tileSize.height));
    
    printf("%f,%f\n",mapSize.width/tileSize.width,mapSize.height/tileSize.height);
    printf("%f, %f, %f, %f, %f\n",mapSize.width/2,tileSize.width,tileSize.height,mPlayerTank[0]->getContentSize().width,mPlayerTank[0]->getContentSize().height);
    
    
    CCPoint xx=mPlayerTank[0]->getPosition();
    printf("tank_Pos: %f,%f\n",xx.x,xx.y);
    
    myPanel = Panel::create();
    
     addChild(myPanel, 3);
    
    /*
    CCTMXTiledMap* tmxFile = CCTMXTiledMap::create("Round1.tmx");
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize(); 
    CCSize size = tmxFile->getContentSize();
    
    // CCSize wSize=CCDirector::sharedDirector()->getVisibleSize();
    // float scale = wSize.height/ size.height;
    
    tmxFile->setPosition(ccp((winSize.width - size.width)/2, (winSize.height - size.height)/2));
    // tmxFile->setScale(scale);
    this->addChild(tmxFile);
    
    
    CCSize tileSize = tmxFile->getTileSize();
    mPlayerTank[0] = Tank::createTankWithTankType("player2U.png");
    CCSize tankSize = mPlayerTank[0]->getContentSize();
    mPlayerTank[0]->setScaleX(tileSize.width * 2 / tankSize.width);
    mPlayerTank[0]->setScaleY(tileSize.height * 2 / tankSize.height);
    mPlayerTank[0]->setPosition(ccp(winSize.width / 2 - tileSize.width * 2, tileSize.height));
    this->addChild(mPlayerTank[0], 2);
    
    
    myPanel = Panel::create();
    addChild(myPanel,3);
    */
    mEnemyAI = EnemyAI::createEnemyAIWithTank(mPlayerTank[0]);
    return true;

}


void CityScene::onEnter() {
    
    CCLayer::onEnter();
    this->scheduleUpdate();
    
}

void CityScene::update(float delta) {
    
    CCLayer::update(delta);
    // 简单的向前运动，用于测试
    // mPlayerTank[0]->setPositionY(mPlayerTank[0]->getPositionY()+1);
    if(mPlayerTank[0] != NULL)
    mPlayerTank[0]->command(myPanel->getOrder());

    mEnemyAI->update(delta);
}



