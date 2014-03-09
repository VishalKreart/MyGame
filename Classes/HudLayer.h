#ifndef __HUD_SCENE_H__
#define __HUD_SCENE_H__

#include "cocos2d.h"
using namespace std;

class HudLayer : public cocos2d::CCLayer
{
public:
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
	static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HudLayer);

	void setString(int coin);
private:
	cocos2d::CCLabelBMFont* coinLabel;
};

#endif // __HUD_SCENE_H__
