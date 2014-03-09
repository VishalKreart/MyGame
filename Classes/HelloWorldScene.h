#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
//#include "GLES-Render.h"
#include "Obstacle.h"
#include "HudLayer.h"
#include <vector>
#include "StoreLayer.h"
#include "cocos-ext.h"
using namespace std;
using namespace cocos2d::extension;
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer,public b2ContactListener
{
public:
	HelloWorld();
	~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	void initPhysics();
	virtual void draw();
	void update(float dt);
	//virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	static int score;
	static bool collisionFlag;
	void GameOver();
	
private:
	CCProgressTimer* progressTimer;
	bool saveMeFlag;
	CCArmature* beeArmature;
	CC_SYNTHESIZE(int,curruntState,curruntState);
	cocos2d::CCSize screenSize;
	b2World* world;
	b2Body * beeBody;
	//GLESDebugDraw * m_debugDraw;
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void saveMeCallback(CCObject* pSender);
	void flipBoolCallback(float dt);
	void addBox(cocos2d::CCPoint point,float width, float height);
	void addBall(cocos2d::CCPoint point,float radius);
	void addPlatform();
	void createSaveMeLayer();
	CCLabelBMFont* pLabel;
	CCLabelTTF* pReady;
	CCLabelTTF* pTap;
    std::vector<Obstacle*> *_pipes;
	CCArray * _groundSprites;
	HudLayer* _hud;
	int scroll;
	void OnPurchaseEvent();
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
};

#endif // __HELLOWORLD_SCENE_H__
