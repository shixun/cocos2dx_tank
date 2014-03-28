//
//  Entity.cpp
//  TankProject
//
//  Created by yyb on 14-3-18.
//
//

#include "Entity.h"



Entity::Entity() {
    
    m_sprite = NULL;
    pos_x = 0;
    pos_y = 0;
    order = ocmdNothing;
    rotation = 0;
}

Entity::~Entity() {
    
}

CCSprite* Entity::getSprite() {
    return this->m_sprite;
}

void Entity::bindSprite(cocos2d::CCSprite *sprite) {
    m_sprite = sprite;
    this->addChild(m_sprite);
}

void Entity::setXY(float x, float y) {
    printf("%f,,,%f\n",x,y);
    
    this->pos_x = x;
    this->pos_y = y;
}

float Entity::getPosx(){
    printf("%f\n",this->pos_x);
    return this->pos_x;
}

float Entity::getPosy() {
    printf("%f\n",this->pos_y);
    return this->pos_y;
}

/*
void Entity::setRotation(float rotation) {
    this->rotation = rotation;
    
}
*/

/*
float Entity::getRotation() {
    return this->rotation;
}
*/

void Entity::setOrder(oenumOrder ord) {
    printf("ord  %d\n",  ord);
    this->order = ord;
}

oenumOrder Entity::getOrder() {
    return this->order;
}









