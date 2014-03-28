//
//  LoginGameScene.cpp
//  TankProject
//
//  Created by yyb on 14-3-17.
//
//

#include "LoginGameScene.h"
#ifdef _WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "GameScene.h"
USING_NS_CC;

#define GATE_HOST "127.0.0.1"   // 10.82.198.120
#define GATE_PORT 3014

static const char* connectorHost = "";
static int connectorPort = 0;
static pc_client_t* pomelo_client = NULL;
static int error = 0;
static std::string channel = "";
static std::string username = "yyb";
static CCArray* playersTankQueue;
static int playerId =0;

bool LoginGameScene::init() {
    
    
    CCSprite* sprite = CCSprite::create("CloseNormal.png");
    sprite->setPosition(ccp(200,200));
    this->addChild(sprite);
    
    
    CCLabelTTF *label = CCLabelTTF::create("Login", "Arial", 50);
    //#endif
    CCMenuItemLabel *pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(LoginGameScene::doLogin));
    CCMenu *pMenu = CCMenu::create(pMenuItem, NULL);
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp(200,300) );
    //m_pEditEmail->setAnchorPoint(ccp(0.5, 1.0f));
    this->addChild(pMenu, 1);
    
    
    
    
    return true;
}


CCScene* LoginGameScene::scene() {
    
    CCScene* scene = CCScene::create();
    LoginGameScene* layer = LoginGameScene::create();
    scene->addChild(layer);
    return scene;
    
}

void LoginGameScene::doLogin() {
    
    const char *ip = GATE_HOST;
    int port = GATE_PORT;
    
    pc_client_t *client = pc_client_new();
    
    struct sockaddr_in address;
    
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip);

    
    if(pc_client_connect(client, &address)) {
        CCLOG("fail to connect to server");
        pc_client_destroy(client);
        return ;
    }
    
    const char *route = "gate.gateHandler.queryEntry";
    json_t *msg = json_object();
    
    json_t *str = json_string(username.c_str());
    json_object_set(msg, "uid", str);
    json_decref(str);
    
    pc_request_t *request = pc_request_new();
    void (*on_request_gate_cb)(pc_request_t *req, int status, json_t *resp) = &LoginGameScene::requstGateCallback;
    
    pc_request(client,request,route,msg,on_request_gate_cb);
    
    //主线程结束 ，等待子线程返回
    pc_client_join(client);
    
    // 销毁连接 
    pc_client_destroy(client);
    
}


void LoginGameScene::requstGateCallback(pc_request_t *req, int status, json_t *resp) {
    
    if(status == -1) {
        CCLOG("fail to send request to server");
    }else if(status == 0) {
        connectorHost = json_string_value(json_object_get(resp, "host"));
        connectorPort = json_number_value(json_object_get(resp, "port"));
        CCLOG("%s %d", connectorHost,connectorPort);
        pc_client_t *client = pc_client_new();

        struct sockaddr_in address;
        memset(&address, 0, sizeof(struct sockaddr_in));
        address.sin_family = AF_INET;
        
        address.sin_port = htons(connectorPort);
        address.sin_addr.s_addr = inet_addr(connectorHost);
        
        void (*on_disconnect)(pc_client_t *client, const char *event, void *data) = &LoginGameScene::onDisconnectCallback;
        /*
        void (*on_move)(pc_client_t *client, const char *event, void *data) = &LoginGameScene::onMoveCallback;
         */
        void (*on_add)(pc_client_t *client, const char *event, void *data) = &LoginGameScene::onAddCallback;
        void (*on_leave)(pc_client_t *client, const char *event, void *data) = &LoginGameScene::onLeaveCallback;
        
        pc_add_listener(client, "disconnect", on_disconnect);
        // pc_add_listener(client, "onMove", on_move);
        pc_add_listener(client, "onAdd", on_add);
        pc_add_listener(client, "onLeave", on_leave);
        
        if(pc_client_connect(client, &address)) {
            CCLOG("fail to connect server");
            pc_client_destroy(client);
            return;
        }
        
        const char *route = "connector.entryHandler.entry";
        json_t *msg = json_object();
        json_t *str = json_string(username.c_str());
        // json_t *channel_str = json_string(channel.c_str());
        json_object_set(msg,"username",str);
        // json_object_set(msg,"rid",channel_str);
        json_decref(str);
        // json_decref(channel_str);
        
        pc_request_t *request = pc_request_new();
        void (*connect_cb)(pc_request_t *req, int status, json_t *resp )= &LoginGameScene::requstConnectorCallback;
        pc_request(client, request, route, msg, connect_cb);
    }

    // release relative resource with pc_request_t
    json_t *pc_msg = req->msg;
    pc_client_t *pc_client = req->client;
    json_decref(pc_msg);
    pc_request_destroy(req);
    
    pc_client_stop(pc_client);
    
}

void LoginGameScene::requstConnectorCallback(pc_request_t *req, int status, json_t *resp) {
    
    error = 0;
    if(status == -1) {
        CCLOG("Fail to send request to server");
    }else if(status == 0) {
        
        char *json_str = json_dumps(resp, 0);
        CCLOG("server resonse:  %s\n",json_str);
        
          json_t *s = json_object_get(resp, "playerId");
        //const char *cs = json_string_value(jres);
        // printf("--%s\n",cs);
        int num = json_number_value(s);
        // printf("pp%d\n",num);
        if(json_object_get(resp,"error")!=NULL) {
            error = 1;
            CCLOG("connect error %s",json_str);
            free(json_str);
            return;
        }
        
        pomelo_client = req->client;
        playerId = num;
    }
    
    
    json_t *msg = req->msg;
  //  pc_client_t *client = req->client;
    json_decref(msg);
    pc_request_destroy(req);
}


void LoginGameScene::dispatchLoginCallbacks(float delta) {
    
    if(pomelo_client == NULL || error == 1) {
        return;
    }
    
   //  CCLOG("ssssssssssss");
    
    CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
    
    CCScene* pScene = CCScene::create();
    
    GameScene* game = new GameScene();
    
    struct sockaddr_in address;
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    
    address.sin_port = htons(connectorPort);
    address.sin_addr.s_addr = inet_addr(connectorHost);
        
    printf("login: playerId %d",playerId);
    game->setAddress(address);
    game->setUserName(username);
    game->setPlayId(playerId);
    game->setClient(pomelo_client);
    CCLOG("init GameScene");
   
    if(game && game->init()) {
        //pLayer->autorelease();
        pScene->addChild(game);
        CCLOG("director replaceScene");
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, pScene));
    } else {
        delete game;
        game = NULL;
    }

    
}

void LoginGameScene::onEnter() {
    
    CCLayer::onEnter();
    CCLOG("Login onEnter");
    pomelo_client = NULL;
    playersTankQueue = new CCArray();
    playersTankQueue->init();
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(LoginGameScene::dispatchLoginCallbacks), this, 0, false);
    
    
}

void LoginGameScene::onAddCallback(pc_client_t *client, const char *event, void *data) {
    
    if(!playersTankQueue) {
        return;
    }
    
    json_t* json = (json_t*)data;
    json_t* user = json_object_get(json,"user");
    const char* msg = json_string_value(user);
    CCLOG("%s %s",event,msg);
    return;
    
    
}


void LoginGameScene::onMoveCallback(pc_client_t *client, const char *event, void *data) {
    
        
    
}


void LoginGameScene::onLeaveCallback(pc_client_t *client, const char *event, void *data) {
    
}

void LoginGameScene::onDisconnectCallback(pc_client_t *client, const char *event, void *data) {
    
    CCLOG("%s", event);
    return;

    
}







