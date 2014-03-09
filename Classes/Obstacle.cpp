#include "Obstacle.h"
#include "GameConstants.h"

Obstacle::~Obstacle()
{

}


Obstacle::Obstacle(cocos2d::CCSprite *topSprite,cocos2d::CCSprite *bottomSprite)
{
	this->topSprite = topSprite;
	this->bottomSprite = bottomSprite;
	this->topSprite->setAnchorPoint(ccp(0,0));
	this->bottomSprite->setAnchorPoint(ccp(0,1));
}

b2Body* Obstacle:: initPhysicsBody(b2World* world,cocos2d::CCPoint pos,cocos2d::CCSprite* sprite)
{
	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position=b2Vec2((pos.x)/PTM_RATIO,pos.y/PTM_RATIO);

	b2Body * body = world->CreateBody(&bodyDef);
	//bodyDef.position.Set(160.0f/PTM_RATIO,240.0f/PTM_RATIO);
	//define shape
	b2PolygonShape box;

	box.SetAsBox((sprite->getContentSize().width/2) /PTM_RATIO, (sprite->getContentSize().height/2) / PTM_RATIO);
	//Define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 2;
	fixtureDef.restitution = 0;
	body->CreateFixture(&fixtureDef);
	return body;
}

b2Body* Obstacle:: initGoal(b2World* world,cocos2d::CCPoint pos,cocos2d::CCSprite* sprite)
{
	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position=b2Vec2((pos.x)/PTM_RATIO,pos.y/PTM_RATIO);

	b2Body * body = world->CreateBody(&bodyDef);
	body->SetUserData((void *) kSensorBody);
	//bodyDef.position.Set(160.0f/PTM_RATIO,240.0f/PTM_RATIO);
	//define shape
	b2PolygonShape box;

	box.SetAsBox((sprite->getContentSize().width/4) /PTM_RATIO, (sprite->getContentSize().height/2) / PTM_RATIO);
	//Define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 2;
	fixtureDef.isSensor = true;
	fixtureDef.restitution = 0;
	body->CreateFixture(&fixtureDef);
	return body;
}

void Obstacle::initObstaclePos(cocos2d::CCPoint topos,cocos2d::CCPoint bottomPos,b2World* world) 
{
	topSprite->setPosition(topos);
	bottomSprite->setPosition(bottomPos);
	//topBody = initPhysicsBody(world,ccp(topos.x+(topSprite->getContentSize().width/2),topos.y+(topSprite->getContentSize().height/2)),this->topSprite);
	//bottomBody = initPhysicsBody(world,ccp(bottomPos.x+(topSprite->getContentSize().width/2),bottomPos.y-(topSprite->getContentSize().height/2)),this->bottomSprite);
	sensorBody = initGoal(world,ccp(topSprite->getPositionX()+(topSprite->getContentSize().width/2),(topSprite->getPositionY()+bottomSprite->getPositionY())/2),this->topSprite);
	this->topPos = topos;
	this->bottomPos = bottomPos;
}

void Obstacle::changePos(cocos2d::CCPoint topos,cocos2d::CCPoint bottomPos)
{
	this->topPos=topos;
	b2Vec2 pos;
	pos.Set((topos.x+(topSprite->getContentSize().width/2))/PTM_RATIO,(topos.y+(topSprite->getContentSize().height/2))/PTM_RATIO);
	//this->topBody->SetTransform(pos,this->topBody->GetAngle());
	this->topSprite->setPosition(topos);

	this->bottomPos=bottomPos;
	pos.Set((bottomPos.x+(topSprite->getContentSize().width/2))/PTM_RATIO,(bottomPos.y-(topSprite->getContentSize().height/2))/PTM_RATIO);
	//this->bottomBody->SetTransform(pos,this->bottomBody->GetAngle());
	this->bottomSprite->setPosition(bottomPos);

	pos.Set((topSprite->getPositionX()+(topSprite->getContentSize().width/2))/PTM_RATIO,((topSprite->getPositionY()+bottomSprite->getPositionY())/2)/PTM_RATIO);
	this->sensorBody->SetTransform(pos,this->sensorBody->GetAngle());
}
