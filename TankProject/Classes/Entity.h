//
//  Entity.h
//  TankProject
//
//  Created by yyb on 14-3-18.
//
//

#ifndef __TankProject__Entity__
#define __TankProject__Entity__

#include <iostream>
#include "cocos2d.h"
#include "const.h"

USING_NS_CC;




class Entity:public CCNode {
    
public:
    Entity();
    ~Entity();
    CCSprite* getSprite();
    void bindSprite(CCSprite* sprite);
    void setXY(float x,float y);
    float getPosx();
    float getPosy();
    //float getRotation();
    // void setRotation(float rotation);
    oenumOrder getOrder();
    void setOrder(oenumOrder ord);
    
    
private:
    CCSprite* m_sprite;
    float pos_x;    // 横坐标
    float pos_y;    //纵坐标
    float rotation;  //朝向
    oenumOrder order;
    
};
#endif /* defined(__TankProject__Entity__) */
