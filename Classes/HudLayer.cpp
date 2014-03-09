#include "Hudlayer.h"
#include "GameConstants.h"
USING_NS_CC;

using namespace cocos2d;

bool HudLayer::init()
{
    if (CCLayer::init()) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
       CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	int coin = CCUserDefault::sharedUserDefault()->getIntegerForKey(kKeyForInitCoin.getCString(),kInitCoin);
	char string[32];
	sprintf(string, "%d", coin);
	coinLabel = CCLabelBMFont::create(string, "font.fnt", visibleSize.width);//CCLabelTTF::create(string, "fonts/MarkerFelt.ttf", 30);
	coinLabel->setPosition(ccp(visibleSize.width-5,visibleSize.height-5));
	coinLabel->setAnchorPoint(ccp(1,1));
	this->addChild(coinLabel);
    }
    
    return true;
}

void HudLayer::setString(int coin)
{
	char string[32];
	sprintf(string, "%d", coin);
	coinLabel->setString(string);
}