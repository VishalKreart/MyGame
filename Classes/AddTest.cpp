#include "AddTest.h"
USING_NS_CC;


CCScene* AddTest::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    AddTest *layer = AddTest::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AddTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ALX::sharedALX()->setAdLoadDelegate(this);
	#endif
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
                                        menu_selector(AddTest::menuCloseCallback));
    
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello applovin-x", "Arial", 40);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    CCMenuItemFont* pShowItem = CCMenuItemFont::create("Show Interstitial", this, menu_selector(AddTest::menuShowCallback));
    pShowItem->setPosition(ccp(origin.x + visibleSize.width/2 ,
                                origin.y + visibleSize.height/2));
    pShowItem->setFontSizeObj(40);
    pMenu->addChild(pShowItem);
    
    
    return true;
}

void AddTest::menuCloseCallback(CCObject* pSender)
{
    
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	ALX::sharedALX()->purgeALX();
    exit(0);
#endif
}


void AddTest::menuShowCallback(CCObject* pSender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ALX::sharedALX()->showInterstitialAd();
	#endif
}

void AddTest::didLoadAd(const char* lable)
{
    CCLOG("didLoadAd: %s", lable);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
}

void AddTest::didFailToLoadAdWithError(int code)
{
    CCLOG("didFailToLoadAdWithError %d", code);
}
