
#include "cocos2d.h"
#include "Box2D\Box2D.h"
class Obstacle  
{
	public:
		Obstacle(cocos2d::CCSprite *topSprite,cocos2d::CCSprite *bottomSprite);
		~Obstacle();
		virtual void initObstaclePos(cocos2d::CCPoint topPos,cocos2d::CCPoint bottomPos,b2World* world);
		//virtual void initObstacleSprite(cocos2d::CCSprite *topSprite,cocos2d::CCSprite *bottomSprite);
		CC_SYNTHESIZE(cocos2d::CCSprite *, topSprite, topSprite);
		CC_SYNTHESIZE(cocos2d::CCSprite *, bottomSprite, bottomSprite);
		CC_SYNTHESIZE(cocos2d::CCPoint , topPos, topPos);
		CC_SYNTHESIZE(cocos2d::CCPoint , bottomPos, bottomPos);
		/*CC_SYNTHESIZE(b2Body * , topBody, topBody);
		CC_SYNTHESIZE(b2Body * , bottomBody, bottomBody);*/
		CC_SYNTHESIZE(b2Body * , sensorBody, sensorBody);
		static b2Body* initPhysicsBody(b2World* world,cocos2d::CCPoint pos,cocos2d::CCSprite* sprite);
		static b2Body* initGoal(b2World* world,cocos2d::CCPoint pos,cocos2d::CCSprite* sprite);
		void changePos(cocos2d::CCPoint topos,cocos2d::CCPoint bottomPos);
};