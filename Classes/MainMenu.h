#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "ApplovinX.h"
#include "HudLayer.h"
using namespace std;

class MainMenu : public cocos2d::CCLayer,public ALXAdLoadDelegate
{
public:
	MainMenu();
	~MainMenu();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
	HudLayer *_hud;
private:
	 void CreateStoreLayer();
	 void playButtonCallback(CCObject* pSender);
	 void rateButtonCallback(CCObject* pSender);
	 void leaderBoardButtonCallback(CCObject* pSender);

	  // ALXAdLoadDelegate method
    void didLoadAd(const char* lable);
    void didFailToLoadAdWithError(int code);
	CCLayer* pStoreLayer;
};

#endif // __MAINMENU_SCENE_H__