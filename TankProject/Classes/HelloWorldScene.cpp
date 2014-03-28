#include "HelloWorldScene.h"
#include "LoginGameScene.h"
// #include "ChoiceScene.h"
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    this->setKeypadEnabled(true);
    
    
    CCMenuItemImage *pItemPlay = CCMenuItemImage::create(
                                                         "playgameNormal.png", "playgameClose.png",this,menu_selector(HelloWorld::menuPlayGameCallback));
    pItemPlay->setPosition(ccp(visibleSize.width / 2, visibleSize.height*1.0f / 4.0f));
    pItemPlay->setScaleX(visibleSize.width / 600);
    pItemPlay->setScaleY(visibleSize.height / 400);
    
    CCMenu *pMenuPlay = CCMenu::create(pItemPlay, NULL);
    pMenuPlay->setPosition(CCPointZero);
    this->addChild(pMenuPlay, 1);
    
    CCSprite *pcSprite  = CCSprite::create("ScenceStart.png");
    pcSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
    CCSize sz = pSprite->getContentSize();
    pcSprite->setScaleX(visibleSize.width / sz.width);
    pcSprite->setScaleY(visibleSize.height / sz.height);
    this->addChild(pcSprite, 0);
    
    return true;
}


void HelloWorld::keyBackClicked() {
    
    CCLayer::keyBackClicked();
    CCDirector::sharedDirector()->end();
    
}

void HelloWorld::keyMenuClicked() {
    
    CCLayer::keyMenuClicked();
    
}

void HelloWorld::menuPlayGameCallback(cocos2d::CCObject *pSender) {
    
    
   // CCScene* pScene = ChoiceScene::scene();
    CCScene*  login = LoginGameScene::scene();
    CCDirector::sharedDirector()->pushScene(login);
    return;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
