//
//  LoginGameScene.h
//  TankProject
//
//  Created by yyb on 14-3-17.
//
//

#ifndef __TankProject__LoginGameScene__
#define __TankProject__LoginGameScene__

#include <iostream>
#include "pomelo.h"
#include "cocos2d.h"



class LoginGameScene: public cocos2d::CCLayer {
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
	CREATE_FUNC(LoginGameScene);

    void dispatchLoginCallbacks(float delta);    
    
    // pomelo handle
   virtual void onEnter();
	void doLogin();
	// pomelo events callback
	static void onMoveCallback(pc_client_t *client, const char *event, void *data);
    //玩家加入
	static void onAddCallback(pc_client_t *client, const char *event, void *data);
	static void onLeaveCallback(pc_client_t *client, const char *event, void *data);
	static void onDisconnectCallback(pc_client_t *client, const char *event, void *data);
    //增加实体  （ai  或  子弹）
    static void onAddEntitysCallback(pc_client_t *client, const char *event, void *data);
	static void requstGateCallback(pc_request_t *req, int status, json_t *resp);
	static void requstConnectorCallback(pc_request_t *req, int status, json_t *resp);
    
};

#endif /* defined(__TankProject__LoginGameScene__) */
