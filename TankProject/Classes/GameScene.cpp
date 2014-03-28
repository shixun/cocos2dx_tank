//
//  GameScene.cpp
//  TankProject
//
//  Created by yyb on 14-3-18.
//
//

#include "GameScene.h"
#include "TileMapInfo.h"
#ifdef _WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>


USING_NS_CC;
using namespace std;


static   CCArray* entityTankQueue;
//static CCArray* entityBulletQueue;
static   std::string userName = "yyb";
static   int playId=0;
static   TileMapInfo* tileMapInfo;
static   TankEntity* myTank;
static   pc_client_t* client;
static struct sockaddr_in address;
static bool isNeting;

bool GameScene::init() {

    bool result = false;
    isNeting = false;
    
    
    CCLayer::init();
    
    tileMapInfo = TileMapInfo::createMapInfoWithFile("Round5.tmx");
    CCTMXTiledMap* tmxTileMap = tileMapInfo->getTileMap();
    this->addChild(tmxTileMap);
    
    myPanel = Panel::create();
    this->addChild(myPanel,3);
    
    /*
    CCSize tileSize = tmxTileMap->getTileSize();
    CCSize mapSize = tmxTileMap->getContentSize();
    myTank = TankEntity::createTankWithTankType("player2U.png", tileMapInfo);
    myTank->setTankType(CCString::createWithFormat("%s","playTank"));
    myTank->setOrder(ocmdNothing);
    if(userName.compare("yyb") == 0) {
        myTank->setPosition(ccp(mapSize.width/2-tileSize.width*3,tileSize.height));
        myTank->setXY(mapSize.width/2-tileSize.width*3, tileSize.height);
        // myTank->setXY(100.0, 100.0);
    }else {
        myTank->setPosition(ccp(mapSize.width/2+tileSize.width*3,tileSize.height));
        myTank->setXY(mapSize.width/2+tileSize.width*3, tileSize.height);
    }
    myTank->setUserId(playId);
    */
    
    result = true;
    return result;
    
}

CCScene* GameScene::scene() {
    
    CCScene *scene = CCScene::create();
    
    GameScene* gameLayer = GameScene::create();
    
    scene->addChild(gameLayer);
    
    return scene;
    
}

void GameScene::setUserQueue(cocos2d::CCArray *userQueue) {
    this->setUserQueue(userQueue);
}

void GameScene::setPlaysTankQueue(cocos2d::CCArray *playTankQueue) {
   // this->setPlaysTankQueue(playsTankQueue);
    
}

void GameScene::setEntityTankQueue(cocos2d::CCArray *entityAIQueue) {
    // this->entityTankQueue = entityAIQueue;
}

void GameScene::setEntityBulletQueue(cocos2d::CCArray *bulletQueue) {
   // this->entityBulletQueue = bulletQueue;
}

void GameScene::setChannel(string channel) {
    this->s_channel = channel;
}


void GameScene::setClient(pc_client_t *pomeloClient) {
     client = pomeloClient;
}

void GameScene::onMovePlaysTankCallback(pc_client_t *client, const char *event, void *data) {
    
       
     json_t* json = (json_t* )data;
     json_t* entityTankId = json_object_get(json, "entityId");
     int id = json_number_value(entityTankId);
     json_t* pos_x = json_object_get(json, "pos_x");
     float x = json_real_value(pos_x);
     json_t* pos_y = json_object_get(json, "pos_y");
     float y = json_real_value(pos_y);
     json_t* order = json_object_get(json, "order");
     int  iorder = json_number_value(order);
    oenumOrder ood;
     if(iorder == 0)
         ood = ocmdNothing;
    if(iorder == 1)
        ood = ocmdGoUP;
    if(iorder == 2)
        ood = ocmdGoRight;
    if(iorder == 3)
        ood = ocmdGoDown;
    if(iorder == 4)
        ood = ocmdGoLeft;
    // CCLOG("call back");
    for(int i=0;i<entityTankQueue->count();i++) {
         TankEntity* tank = (TankEntity*)entityTankQueue->objectAtIndex(i);
         if( tank->getEntityId() == id ) {
             tank->setXY(x, y);
             tank->setOrder(ood);
             tank->move(x, y);
             break;
         }
    
     }
    
    
}


void GameScene::onMoveEntityTankCallback(pc_client_t *client, const char *event, void *data) {
    
}

void GameScene::onMoveEntityBulletCallback(pc_client_t *client, const char *event, void *data) {
    
}

void GameScene::onAddPlaysTankCallback(pc_client_t *client, const char *event, void *data) {
    
}

void GameScene::onRemovePlaysTankCallback(pc_client_t *client, const char *event, void *data) {
    
}


void GameScene::onAddEntityTankCallback(pc_client_t *client, const char *event, void *data) {
    
    json_t* json = (json_t* )data;
    json_t* entities = json_object_get(json, "entities");
    int length = json_array_size(entities);
    for(int i=0;i<length;i++) {
        json_t* temp = json_array_get(entities, i);
        json_t* id = json_object_get(temp, "id");
        int intId = json_number_value(id);
        printf("intId: %d\n",intId);
        if(intId == playId) {
            continue;
        }
        
        json_t* entityId = json_object_get(temp, "entityId");
        int entiId = json_number_value(entityId);
        json_t* type = json_object_get(temp, "type");
        const char* ty = json_string_value(type);
        json_t* pos_x = json_object_get(temp, "x");
        float x = json_integer_value(pos_x);
        json_t* pos_y = json_object_get(temp, "y");
        float y = json_integer_value(pos_y);
        json_t* order = json_object_get(temp, "order");
        int   iorder = json_number_value(order);
        TankEntity* tank;
        const char * str1 = "player";
        const char * str2 = "entitytank";
        if(strcmp(ty, str1) == 0) {
            
            //tank = TankEntity::createTankWithTankType("player2U.png", tileMapInfo);
            tank = new TankEntity();
            tank->setEntityId(entiId);
            tank->setXY(x, y);
            // tank->setPosition(ccp(x,y));
            tank->setOrder(ocmdBorn);
            tank->setUserId(intId);
            tank->setTankType(CCString::createWithFormat("%s",ty));
        }
        if(strcmp(ty, str2) == 0) {
            
        }
        
        if(tank != NULL)
        entityTankQueue->addObject(tank);
    }
    
    
    
    
}

void GameScene::onRemoveEntityTankCallback(pc_client_t *client, const char *event, void *data) {
    
}

void GameScene::onAddEntityBulletCallback(pc_client_t *client, const char *event, void *data) {
    
}

void GameScene::onRemoveEntityBulletCallback(pc_client_t *client, const char *event, void *data) {
    
}


void GameScene::onHitTankCallback(pc_client_t *client, const char *event, void *data) {
    
}

void GameScene::onHitMapCallback(pc_client_t *client, const char *event, void *data) {
    
}


void GameScene::onEnter() {
    
    CCLayer::onEnter();
    onEnterScene();
    entityTankQueue = new CCArray();
    entityTankQueue->init();
   
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameScene::updateViewCallback), this, 0, false);
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameScene::updateRequest), this, 0.1f, false);
    /*
    CCDirector::sharedDirector()->getScheduler()->scheduleScriptFunc(<#unsigned int nHandler#>, float fInterval, <#bool bPaused#>)
    */
}


void GameScene::updateViewCallback(float delta) {
    
          
    if(!entityTankQueue) {
        return;
    }
    if(!myTank){
        return;
    }
    
    if(myTank->getOrder() == ocmdBorn)  {
        this->bornTank(myTank);
    }else if(myTank->getOrder() == ocmdFire) {
        CCLOG("fire!");
    }else if(myTank->getOrder() == ocmdFix) {
        myTank->setPosition(myTank->getPosx(),myTank->getPosy());
    }else {
        myTank->update(delta);
    }
    
    /*
    if(entityTankQueue->count() == 0) {
        return;
    }
    */
    CCObject* eTob;
    CCARRAY_FOREACH(entityTankQueue, eTob) {
        TankEntity* tank = (TankEntity*)eTob;
        if(tank->getOrder() == ocmdBorn) {
            this->bornTank(tank);
        }else if(tank->getOrder() == ocmdFire) {
            
        }else {
            tank->update(delta);
        }
    }
    
}


void GameScene::bornTank(TankEntity *tank) {
    
    /*
    if(!tank->getIsCache()) {
        tank->initTankFrame();
    }
    */
    
    tank->initTankWithTankType("player2U.png", tileMapInfo);
    tank->setPosition(tank->getPosx(),tank->getPosy());
    tank->setOrder(ocmdNothing);
    tank->autorelease();
}


void GameScene::setUserName(std::string myuserName) {
    // this->userName = userName;
    userName = myuserName;
}

std::string GameScene::getUserName() {
    // return this->userName;
    return userName;
}


void GameScene::setPlayId(int playerId) {
    // this->playId = playId;
    playId = playerId;
    
}


int GameScene::getPlayId() {
    // return this->playId;
    return playId;
}

void GameScene::onEnterScene() {
    
    
    
    const char *route = "area.playerHandler.enterScene";
    json_t *msg = json_object();
    //json_object_set(msg, "name", userName);
    //json_object_set(msg, "playerId", playerId);
    json_t *name = json_string(userName.c_str());
    // json_decref(name);
    json_t *play = json_integer(playId);
    // json_decref(play);
    printf("playerId:   %d\n",playId);
    json_object_set(msg, "userName", name);
    json_object_set(msg, "playerId", play);
    pc_request_t *request = pc_request_new();
    void (*on_enter_cb)(pc_request_t * req, int status, json_t * resp) = GameScene:: onEnterSceneCallBack;
    pc_request(client, request, route, msg, on_enter_cb);
        
}


void GameScene::onEnterSceneCallBack(pc_request_t *req, int status, json_t *resp) {
    
    if(status == -1) {
        // const char *s = json_dumps(resp, 0);
        json_t* json = json_object_get(resp,"error");
        // CCLOG("ww%s\n",json_string_value(json));
        CCLOG("fail to send request to server");
    }else if(status == 0) {
        
        const char* str = json_dumps(resp, 0);
        CCLOG("server response:hhhhhhh       %s",str);
        
        /*
        CCTMXTiledMap* tmxTileMap = tileMapInfo->getTileMap();
        CCSize tileSize = tmxTileMap->getTileSize();
        CCSize mapSize = tmxTileMap->getContentSize();
        myTank = TankEntity::createTankWithTankType("player2U.png", tileMapInfo);
        myTank->setTankType(CCString::createWithFormat("%s","playTank"));
        myTank->setOrder(ocmdBorn);
        if(userName.compare("yyb") == 0) {
            // myTank->setPosition(ccp(mapSize.width/2-tileSize.width*3,tileSize.height));
            myTank->setXY(mapSize.width/2-tileSize.width*3, tileSize.height);
            // myTank->setXY(100.0, 100.0);
        }else {
            // myTank->setPosition(ccp(mapSize.width/2+tileSize.width*3,tileSize.height));
            myTank->setXY(mapSize.width/2+tileSize.width*3, tileSize.height);
        }
        myTank->setUserId(playId);
        */
        json_t* json = (json_t* )resp;
        json_t* data = json_object_get(json, "data");
        CCTMXTiledMap* tmxTileMap = tileMapInfo->getTileMap();
        CCSize tileSize = tmxTileMap->getTileSize();
        CCSize mapSize = tmxTileMap->getContentSize();
        myTank = new TankEntity();
        myTank->setTankType(CCString::createWithFormat("%s","playTank"));
        myTank->setOrder(ocmdBorn);
        if(userName.compare("yyb") == 0) {
            myTank->setXY(mapSize.width/2-tileSize.width*3, tileSize.height);
        }else {
            myTank->setXY(mapSize.width/2+tileSize.width*3, tileSize.height);
        }
        json_t* playerEntityId = json_object_get(data, "entityId");
        int myEntityId = json_integer_value(playerEntityId);
        myTank->setEntityId(myEntityId);
        myTank->setUserId(playId);
        
        //json_t* json = (json_t* )resp;
       //  json_t* data = json_object_get(json, "data");
        json_t* entities = json_object_get(data, "entities");
        //CCLOG("play: %s",json_dumps(play, 0));
        // json_
       int length = json_array_size(entities);
       for(int i=0;i<length;i++) {
            json_t* temp = json_array_get(entities, i);
            json_t* id = json_object_get(temp, "id");
            int intId = json_number_value(id);
            printf("intId: %d\n",intId);
            if(intId == playId) {
                continue;
            }
            json_t* entityId = json_object_get(temp, "entityId");
            int entiId = json_number_value(entityId);
            json_t* type = json_object_get(temp, "type");
            const char* ty = json_string_value(type);
            json_t* pos_x = json_object_get(temp, "x");
            float x = json_integer_value(pos_x);
            printf("call_x: %f\n",x);
            json_t* pos_y = json_object_get(temp, "y");
            float y = json_integer_value(pos_y);
            printf("call_x: %f\n",y);
            json_t* order = json_object_get(temp, "order");
            int   iorder = json_number_value(order);
            TankEntity* tank;
            const char * str1 = "player";
            const char * str2 = "entitytank";
            if(strcmp(ty, str1) == 0) {
                
                //tank = TankEntity::createTankWithTankType("player2U.png", tileMapInfo);
                tank = new TankEntity();
                tank->setEntityId(entiId);
                tank->setXY(x, y);
                // tank->setPosition(ccp(x,y));
                tank->setOrder(ocmdBorn);
                tank->setUserId(intId);
                tank->setTankType(CCString::createWithFormat("%s",ty));
            }
            if(strcmp(ty, str2) == 0) {
                
            }
            
            if(tank != NULL)
                entityTankQueue->addObject(tank);
        }

                
    }
       
    void (*on_movePlaysTank)(pc_client_t *client, const char *event, void *data) =&GameScene::onMovePlaysTankCallback;
    void (*on_moveEntityTank)(pc_client_t *client, const char *event, void *data)=&GameScene::
    onMoveEntityTankCallback;
    void (*on_addPlaysTank)(pc_client_t *client, const char *event, void *data) =&GameScene::
    onAddPlaysTankCallback;
    void (*on_removePlaysTank)(pc_client_t *client, const char *event, void *data) =&GameScene::
    onRemovePlaysTankCallback;
    void (*on_addEntityTank)(pc_client_t *client, const char *event, void *data) =&GameScene::
    onAddEntityTankCallback;
    void (*on_removeEntityTank)(pc_client_t *client, const char *event, void *data) =&GameScene::
    onRemoveEntityTankCallback;
    // void (*)
    void (*on_moveEntityBullet)(pc_client_t *client, const char *event, void *data)=&GameScene::onMoveEntityBulletCallback;
    void (*on_addEntityBullet)(pc_client_t *client, const char *event, void *data)=&GameScene::onAddEntityBulletCallback;
    void(*on_removeEntityBullet)(pc_client_t *client, const char *event, void *data)=&GameScene::
    onRemoveEntityBulletCallback;
    void(*on_hitTank)(pc_client_t *client, const char *event, void *data)=&GameScene::onHitTankCallback;
    void(*on_hitMap)(pc_client_t *client, const char *event, void *data)=&GameScene::
    onHitMapCallback;
    void(*on_fixTankPos)(pc_client_t *client, const char *event, void *data)=&GameScene::onFixTankPosCallback;
    
    
    pc_add_listener(client, "onMovePlaysTank", on_movePlaysTank);
    pc_add_listener(client, "onMoveEntityTank", on_moveEntityTank);
    pc_add_listener(client, "onAddPlaysTank", on_addPlaysTank);
    pc_add_listener(client, "onRemovePlaysTank", on_removePlaysTank);
    pc_add_listener(client, "onAddEntityTank", on_addEntityTank);
    pc_add_listener(client, "onRemoveEntityTank", on_removeEntityTank);
    pc_add_listener(client, "onMoveEntityBullet", on_moveEntityBullet);
    pc_add_listener(client, "onRemoveEntityBullet", on_removeEntityBullet);
    pc_add_listener(client, "onAddEntityBullet", on_addEntityBullet);
    pc_add_listener(client, "onHitTank", on_hitTank);
    pc_add_listener(client, "onHitMap", on_hitMap);
    pc_add_listener(client, "onFixTankPos", on_fixTankPos);

    
    
    json_t *msg = req->msg;
    json_decref(msg);
    pc_request_destroy(req);
    
    
   //  pc_client_stop(client);
}


void GameScene::onMove() {
    
    int order = 0;
    
    if(!myTank)
        return;
    
   switch(myPanel->getOrder()) {
        case cmdNothing:
            order = 0;
            break;
        case cmdGoUP:
            order = 1;
            break;
        case cmdGoRight:
            order = 2;
            break;
        case cmdGoDown:
            order = 3;
            break;
        case cmdGoLeft:
            order = 4;
            break;
       case cmdFire:
           break;
    }
    
    if(order == 0)
        return;
    
    // myTank->setOrder(ocmdNet);
    const char *route = "area.playerHandler.move";
    json_t *msg = json_object();
    //json_object_set(msg, "name", userName);
    //json_object_set(msg, "playerId", playerId);
    json_t *name = json_string(userName.c_str());
    // json_decref(name);
    json_t *play = json_integer(playId);
    // json_decref(play);
    json_t *pos_x = json_real(myTank->getPosx());
    // json_decref(pos_x);
    json_t *pos_y = json_real(myTank->getPosy());
    // json_decref(pos_y);
    json_t *jorder = json_integer(order);
    // json_decref(jorder);
    json_object_set(msg, "userName", name);
    json_object_set(msg, "playerId", play);
    json_object_set(msg, "pos_x", pos_x);
    json_object_set(msg, "pos_y", pos_y);
    json_object_set(msg, "order", jorder);
    
    pc_request_t *request = pc_request_new();
    void (*on_enter_cb)(pc_request_t * req, int status, json_t * resp) = &GameScene::onMoveCallBack;
    pc_request(client, request, route, msg, on_enter_cb);
    isNeting = true;
    CCLOG("     neting worked ! ");

}


void GameScene::onMoveCallBack(pc_request_t *req, int status, json_t *resp) {
    
    if(status == -1) {
        CCLOG("fail to send request to server");
        isNeting = false;
    }else if(status == 0) {
        
        
        CCLOG("onMoveCallBack %s",json_dumps(resp, 0));
        json_t* json = (json_t* )resp;
        json_t* pos_x = json_object_get(json, "pos_x");
        float x = json_integer_value(pos_x);
        printf("x: %f\n",x);
        json_t* pos_y = json_object_get(json, "pos_y");
        float y = json_integer_value(pos_y);
        printf("y: %f\n",y);
        json_t* order = json_object_get(json, "order");
        int  iorder = json_integer_value(order);
        printf("order: %d\n",iorder);
        oenumOrder ood;
        if(iorder == 0)  {
            ood = ocmdNothing;  }
        if(iorder == 1)  {
            ood = ocmdGoUP;  }
        if(iorder == 2)  {
            ood = ocmdGoRight;  }
        if(iorder == 3)   {
            ood = ocmdGoDown;  }
        if(iorder == 4)  {
            ood = ocmdGoLeft;   }
        
       
        myTank->setOrder(ood);
        myTank->setXY(x, y);
        myTank->move(x, y);
            }
    
    json_t *msg = req->msg;
    json_decref(msg);
    pc_request_destroy(req);
    isNeting = false;
    
}



void GameScene::setAddress(struct sockaddr_in add) {
      address = add;
}

void GameScene::onFixTankPosCallback(pc_client_t *client, const char *event, void *data) {
    
    json_t* json = (json_t*)data;
    json_t* entityId = json_object_get(json, "entityId");
    int entiId = json_integer_value(entityId);
    json_t* pos_x = json_object_get(json, "pos_x");
    float x = json_integer_value(pos_x);
    json_t* pos_y = json_object_get(json, "pos_y");
    float y = json_integer_value(pos_y);
    json_t* ord = json_object_get(json, "order");
    int order = json_integer_value(ord);
    
    if(myTank->getEntityId() == entiId) {
        myTank->setXY(x, y);
        myTank->setOrder(ocmdFix);
    }
     
}

void GameScene::updateRequest(float delta) {
    
    
    if(!isNeting) {
        this->onMove();
       //  CCLOG("isNeting work !");
    }

}




