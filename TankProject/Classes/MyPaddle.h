//
//  MyPaddle.h
//  TankProject
//
//  Created by yyb on 14-1-10.
//
//

#ifndef __TankProject__MyPaddle__
#define __TankProject__MyPaddle__

#include <iostream>
#include "cocos2d.h"
#include "Paddle.h"
#include "ChoiceScene.h"
using namespace cocos2d;

enum enum_evt {
	evt_start,
	evt_pressA,
	evt_pressB,
	evt_text
};

class MyPaddle :public Paddle {
    
     CC_SYNTHESIZE(enum_evt, m_evttyp, evttyp); 
     CC_SYNTHESIZE(ChoiceScene*, m_pSence, pSence); 
    
public:

   virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
   virtual void ccTouchEnded(CCTouch* touch, CCEvent* event); 
   
  static MyPaddle* paddleWithTexture(CCTexture2D* pTexture);

private:

bool bFlag = false;

};

#endif /* defined(__TankProject__MyPaddle__) */
