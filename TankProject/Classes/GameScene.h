//
//  GameScene.h
//  TankProject
//
//  Created by yyb on 14-3-18.
//
//

#ifndef __TankProject__GameScene__
#define __TankProject__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "pomelo.h"
#include "Panel.h"
#include "TankEntity.h"
#include "const.h"
// using namespace std;


class GameScene:public cocos2d::CCLayer {
  
public:
    virtual bool init();
    virtual void onEnter();
    static CCScene* scene();
    CREATE_FUNC(GameScene);
    
    void setChannel(std::string  channel);
    void setClient(pc_client_t* pomeloClient);
    void setPlaysTankQueue(CCArray* playTankQueue);
    void setEntityTankQueue(CCArray* entityAIQueue);
    void setEntityBulletQueue(CCArray* bulletQueue);
    void setUserQueue(CCArray* userQueue);
    void updateViewCallback(float delta);
    void setAddress(struct sockaddr_in add);
    void bornTank(TankEntity *tank);
    void updateRequest(float delta);
    
    
    void setUserName(std::string myuserName);
    std::string getUserName();
    void setPlayId(int playerId);
    int getPlayId();
    
    
    
   virtual  void onMove();
   virtual void onEnterScene();
   static void onEnterSceneCallBack(pc_request_t *req, int status, json_t *resp);
    
    static   void onMoveCallBack(pc_request_t *req, int status, json_t *resp);
   //移动玩家的坦克，不包括ai坦克
  static void onMovePlaysTankCallback(pc_client_t *client, const char *event, void *data);
   //移动AI坦克不包括玩家坦克
  static  void onMoveEntityTankCallback(pc_client_t *client, const char *event, void *data);
    
  static  void onMoveEntityBulletCallback(pc_client_t *client, const char *event, void *data);
  static void onAddPlaysTankCallback(pc_client_t *client, const char *event, void *data);
  static void onRemovePlaysTankCallback(pc_client_t *client, const char *event, void *data);
  static  void onAddEntityTankCallback(pc_client_t *client, const char *event, void *data);
  static  void onRemoveEntityTankCallback(pc_client_t *client, const char *event, void *data);
  static  void onAddEntityBulletCallback(pc_client_t *client, const char *event, void *data);
  static  void onRemoveEntityBulletCallback(pc_client_t *client, const char *event, void *data);
    
    static void onFixTankPosCallback(pc_client_t *client, const char *event, void *data);
  static void onHitTankCallback(pc_client_t *client, const char *event, void *data);
  static  void onHitMapCallback(pc_client_t *client, const char *event, void *data);
    
    
   //static CCArray* userQueue;
   //static CCArray* playsTankQueue;
    /*
  static  CCArray* entityTankQueue;
   //static CCArray* entityBulletQueue;
  static   std::string userName;
  static    std::string playId;
  static   TileMapInfo* tileMapInfo;
  static   TankEntity* myTank;
    */
    
private:
          Panel* myPanel;
         //  pc_client_t* client;
         std::string s_channel;
       // TankEntity* myTank;
          // TileMapInfo* tileMapInfo;
};


#endif /* defined(__TankProject__GameScene__) */
