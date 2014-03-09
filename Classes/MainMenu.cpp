#include "MainMenu.h"
#include "HelloWorldScene.h"
#include "Store/StoreConfig.h"
#include "Store/StoreManager.h"
#include "StoreLayer.h"
#include "HudLayer.h"
#include "Extension\CCHelper.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif
#define  CLASS_NAME "com/fun/myproject/MyGame"
USING_NS_CC;

CCScene* MainMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
	MainMenu* layer = new MainMenu();
    scene->addChild(layer);

	HudLayer *hud = new HudLayer();
    hud->init();
    scene->addChild(hud);
    layer->_hud = hud;

    layer->release();
	
    // return the scene
    return scene;
}

MainMenu::~MainMenu()
{
}

MainMenu::MainMenu()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	CCSprite *bg = CCSprite::create("splash.png");
	bg->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg,0);


	 CCMenuItemImage *playItem = CCMenuItemImage::create(
                                        "btn_play.png",
                                        "btn_play_focus.png",
                                        this,
										menu_selector(MainMenu::playButtonCallback));
	 playItem->setPosition(visibleSize.width/2,(visibleSize.height/2)-(playItem->getContentSize().height/2));

	CCMenuItemImage *rateItem = CCMenuItemImage::create(
                                        "btn_rateus.png",
                                        "btn_rateus_focus.png",
                                        this,
										menu_selector(MainMenu::rateButtonCallback));

	rateItem->setPosition((visibleSize.width/2)-rateItem->getContentSize().width+20,(visibleSize.height/2)-rateItem->getContentSize().height-(playItem->getContentSize().height/2));

	CCMenuItemImage *leaderBoardItem = CCMenuItemImage::create(
                                        "btn_best.png",
                                        "btn_best_focus.png",
                                        this,
										menu_selector(MainMenu::leaderBoardButtonCallback));
	
	leaderBoardItem->setPosition((visibleSize.width/2)+rateItem->getContentSize().width-20,(visibleSize.height/2)-rateItem->getContentSize().height-(playItem->getContentSize().height/2));

	CCMenu* pMenu = CCMenu::create(playItem,rateItem,leaderBoardItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CreateStoreLayer();
}

void MainMenu::CreateStoreLayer()
{
		pStoreLayer=StoreLayer::getInstance()->getLayer();
		pStoreLayer->setVisible(false);

		this->addChild(pStoreLayer,10);
}

void MainMenu::playButtonCallback(CCObject* pSender)
{
	pStoreLayer->removeFromParentAndCleanup(false);
	CCTransitionFade * trans = CCTransitionFade::create( 0.5f, HelloWorld::scene(), ccBLACK );
	CCDirector::sharedDirector() -> replaceScene( trans );
	
}

void MainMenu::rateButtonCallback(CCObject* pSender)
{
	CCHelper::RateApp();
}

void MainMenu::leaderBoardButtonCallback(CCObject* pSender)
{
		#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
        
        if (!  JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showLeaderboards", "()V"))
        {
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
		#endif
}

void MainMenu::didLoadAd(const char* lable)
{
    CCLOG("didLoadAd: %s", lable);
}

void MainMenu::didFailToLoadAdWithError(int code)
{
    CCLOG("didFailToLoadAdWithError %d", code);
}  
