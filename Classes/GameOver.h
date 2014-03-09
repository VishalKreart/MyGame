#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "ApplovinX.h"
using namespace std;

class GameOver : public cocos2d::CCLayer, public ALXAdLoadDelegate
{
public:
	GameOver();
	~GameOver();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
	
private:
	 void leaderBoardButtonCallback(CCObject* pSender);
	 void upDateHighScore(int score);
	 void playButtonCallback(CCObject* pSender);
	 // ALXAdLoadDelegate method
    void didLoadAd(const char* lable);
    void didFailToLoadAdWithError(int code);
};

#endif // __GAMEOVER_SCENE_H__
