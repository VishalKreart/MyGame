#include "GameOver.h"
#include "HelloWorldScene.h"
#include "GameConstants.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif
#define  CLASS_NAME "com/fun/myproject/MyGame"
USING_NS_CC;


CCScene* GameOver::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
	CCLayer* layer = new GameOver();
    scene->addChild(layer);
    layer->release();
	
    // return the scene
    return scene;
}

GameOver::~GameOver()
{

}

void GameOver::upDateHighScore(int score)
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t
									   , CLASS_NAME
									   , "updateTopScoreLeaderboard"
									   , "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, score);
		// Release
		t.env->DeleteLocalRef(t.classID);
	}
	CCLog("upscore");
	#endif
}

GameOver::GameOver()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//ALX::sharedALX()->setAdLoadDelegate(this);
	#endif

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
 
	int bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(kKeyForBestScore.getCString(),0);
	
	if(HelloWorld::score>bestScore)
	{
		upDateHighScore(HelloWorld::score);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(kKeyForBestScore.getCString(),HelloWorld::score);
        CCUserDefault::sharedUserDefault()->flush();
	}
	bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(kKeyForBestScore.getCString(),0);

	CCSprite *bg = CCSprite::create("bg.png");
	bg->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg,0);

	CCSprite* popUp = CCSprite::create("popup.png");
	popUp->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(popUp,0);

	//best score
	CCSprite* bestScoreText = CCSprite::create("text_bestscore.png");
	bestScoreText->setPosition(ccp(visibleSize.width/2-120,visibleSize.height/2));
	bestScoreText->setAnchorPoint(ccp(0,0.5f));
	this->addChild(bestScoreText,0);
	
	char string[32];
	sprintf(string, "%d", bestScore);
	CCLabelTTF* pLabel = CCLabelTTF::create(string, "fonts/MarkerFelt.ttf", 30);
	pLabel->setPosition(ccp(visibleSize.width/2+50,visibleSize.height/2));
	pLabel->setAnchorPoint(ccp(0,0.5f));
	this->addChild(pLabel,0);
	//best score end

	//your score
	CCSprite* yourScoreText = CCSprite::create("text_yourscore.png");
	yourScoreText->setPosition(ccp(visibleSize.width/2-120,(visibleSize.height/2)+(bestScoreText->getContentSize().height*2)));
	yourScoreText->setAnchorPoint(ccp(0,0.5f));
	this->addChild(yourScoreText,0);

	sprintf(string, "%d", HelloWorld::score);
	pLabel = CCLabelTTF::create(string, "fonts/MarkerFelt.ttf", 30);
	pLabel->setPosition(ccp(visibleSize.width/2+50,(visibleSize.height/2)+(bestScoreText->getContentSize().height*2)));
	pLabel->setAnchorPoint(ccp(0,0.5f));
	this->addChild(pLabel,0);
	//your score end

	//trophy
	CCSprite* trophyText = CCSprite::create("text_trophy.png");
	trophyText->setPosition(ccp(visibleSize.width/2-120,(visibleSize.height/2)-(bestScoreText->getContentSize().height*2)));
	trophyText->setAnchorPoint(ccp(0,0.5f));
	this->addChild(trophyText,0);

	CCSprite* trophy = CCSprite::create("trophy_blank.png");
	int id = HelloWorld::score/10; 
	switch (id)
	{
		case 1 :
			trophy = CCSprite::create("trophy_bronze.png");
		break;

		case 2 :
			trophy = CCSprite::create("trophy_silver.png");
		break;

		case 3 :
			trophy = CCSprite::create("trophy_gold.png");
		break;

		default :
				if(id>3)
					trophy = CCSprite::create("trophy_gold.png");
		break;
	}
	trophy->setPosition(ccp(visibleSize.width/2+50,(visibleSize.height/2)-(bestScoreText->getContentSize().height*2)));
	trophy->setAnchorPoint(ccp(0,0.5f));
	this->addChild(trophy,0);

	//trophy end

	CCSprite* gameOverText = CCSprite::create("text_gameover.png");
	gameOverText->setPosition(ccp(visibleSize.width/2,visibleSize.height-(visibleSize.height/4)));
	this->addChild(gameOverText,0);

	CCSprite* ground = CCSprite::create("base.png");
	ground->setPosition(ccp(0,0));
	ground->setAnchorPoint(ccp(0,0));
	this->addChild(ground,1);


	CCMenuItemImage *playItem = CCMenuItemImage::create(
                                        "btn_play.png",
                                        "btn_play_focus.png",
                                        this,
										menu_selector(GameOver::playButtonCallback));
	playItem->setPosition((visibleSize.width/2)-playItem->getContentSize().width+20,(visibleSize.height/2)-playItem->getContentSize().height-50);
	
	CCMenuItemImage *leaderBoardItem = CCMenuItemImage::create(
                                        "btn_best.png",
                                        "btn_best_focus.png",
                                        this,
										menu_selector(GameOver::leaderBoardButtonCallback));
	
	leaderBoardItem->setPosition((visibleSize.width/2)+playItem->getContentSize().width-20,(visibleSize.height/2)-playItem->getContentSize().height-50);

	CCMenu* pMenu = CCMenu::create(playItem,leaderBoardItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//ALX::sharedALX()->showInterstitialAd();
	#endif
}



void GameOver::playButtonCallback(CCObject* pSender)
{
	CCTransitionFade * trans = CCTransitionFade::create( 0.5f, HelloWorld::scene(), ccBLACK );
	CCDirector::sharedDirector() -> replaceScene( trans );
}

void GameOver::leaderBoardButtonCallback(CCObject* pSender)
{
	//CCTransitionFade * trans = CCTransitionFade::create( 0.5f, HelloWorld::scene(), ccBLACK );
	//CCDirector::sharedDirector() -> replaceScene( trans );
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

void GameOver::didLoadAd(const char* lable)
{
    CCLOG("didLoadAd: %s", lable);
	
}

void GameOver::didFailToLoadAdWithError(int code)
{
    CCLOG("didFailToLoadAdWithError %d", code);
}