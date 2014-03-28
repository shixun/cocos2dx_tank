//
//  Panel.cpp
//  TankProject
//
//  Created by yyb on 14-1-10.
//
//

#include "Panel.h"


bool Panel::init() {
    
    
    CCLayer::init();
    
    CCTexture2D* paddleTexture = CCTextureCache::sharedTextureCache()->addImage(RES_PADDLE_UP);
    m_pPaddleUp = Paddle::paddleWithTexture(paddleTexture); 
    
    paddleTexture = CCTextureCache::sharedTextureCache()->addImage(RES_PADDLE_DOWN);
    m_pPaddleDown = Paddle::paddleWithTexture(paddleTexture);
    
    paddleTexture = CCTextureCache::sharedTextureCache()->addImage(RES_PADDLE_LEFT);
    m_pPaddleLeft = Paddle::paddleWithTexture(paddleTexture);
    
    paddleTexture = CCTextureCache::sharedTextureCache()->addImage(RES_PADDLE_RIGHT);
    m_pPaddleRight = Paddle::paddleWithTexture(paddleTexture);
    
    paddleTexture = CCTextureCache::sharedTextureCache()->addImage(RES_PADDLE_FIRE); 
    m_pPaddleFire = Paddle::paddleWithTexture(paddleTexture);
    
    CCSize size = getContentSize();
    
    //设置手柄上下左右按钮以及开火按钮的位置
    int localX[5] = { size.width*4.5f / 26, size.width*4.5f / 26, size.width*2.3f / 26,
        size.width*6.7f / 26, size.width*22.0f / 26 };
    
    int localY[5] = { size.height*6.7 / 26, size.height*2.3 / 26, size.height*4.5f / 26,
        size.height*4.5f / 26, size.height*5.0 / 26 };
    
    Paddle* paddle[] = { m_pPaddleUp, m_pPaddleDown, m_pPaddleLeft, m_pPaddleRight, m_pPaddleFire }; 
    
    for(int i=0;i<sizeof(paddle)/sizeof(paddle[0]);i++) {
        
        addChild(paddle[i]);
        paddle[i]->setPosition(ccp(localX[i],localY[i]));
        CCSize szPaddle = paddle[i]->getContentSize();
        paddle[i]->setScale(size.height * 4.5f / 26 / szPaddle.height);
        
    }
    
    return true;
    
    
}


enumOrder Panel::getOrder() {
    
    enumOrder order = cmdNothing;
    if(m_pPaddleUp->getstate() == kPaddleStateGrabbed) {
        order = cmdGoUP;
    }else if(m_pPaddleDown->getstate() == kPaddleStateGrabbed) {
        order = cmdGoDown;
    }else if(m_pPaddleLeft->getstate() == kPaddleStateGrabbed) {
        order = cmdGoLeft;
    }else if(m_pPaddleRight->getstate() == kPaddleStateGrabbed) {
        order = cmdGoRight;
    }else if(m_pPaddleFire->getstate() == kPaddleStateGrabbed) {
        order = cmdFire;
    }
    
    return order;
    
}








