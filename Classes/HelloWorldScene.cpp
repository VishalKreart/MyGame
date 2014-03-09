#include "HelloWorldScene.h"
#include "GameConstants.h"
#include "GameOver.h"
#include "StoreLayer.h"
//#include "Obstacle.h"
USING_NS_CC;

static const float kGravity = -30;
static const float kDensity = 1.15;
static const float kMaxVelocity = 10;
static const int kNoOfPipes = 2;
static const int kDistanceBetweenObstacle = 170;
static const int kGapBetweenObstacle = 100;
static const int kScrollSpeed = 130;

int HelloWorld::score;
bool HelloWorld::collisionFlag = true;

static const float randomFloat(float Min, float Max)
{
	return floor(((rand() % RAND_MAX) / (RAND_MAX * 1.0)) * (Max - Min) + Min);
}

CCScene* HelloWorld::scene()
{
	
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// add layer as a child to scene
	HelloWorld* layer = new HelloWorld();
	scene->addChild(layer);

	HudLayer *hud = new HudLayer();
    hud->init();
    scene->addChild(hud);
    layer->_hud = hud;

	// return the scene
	return scene;
}

HelloWorld::HelloWorld()
{
	saveMeFlag = false;
	scroll = kScrollSpeed;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	screenSize = CCDirector::sharedDirector()->getVisibleSize();

	setcurruntState(kGameReady);

	CCSprite *bg = CCSprite::create("bg.png");
	bg->setPosition(ccp(screenSize.width/2,screenSize.height/2));
	this->addChild(bg,0);

	CCSprite *cloud = CCSprite::create("clouds.png");
	cloud->setPosition(ccp(0,screenSize.height-(cloud->getContentSize().height)*(1.5)));
	cloud->setAnchorPoint(ccp(0,0));
	this->addChild(cloud,0);

	_groundSprites = CCArray::createWithCapacity(2);
	_groundSprites->retain();

	for (int i = 0; i < _groundSprites->capacity(); i++)
	{
		CCSprite* ground = CCSprite::create("base.png");
		ground->setPosition(ccp((ground->getContentSize().width*i),0));
		ground->setAnchorPoint(ccp(0,0));
		this->addChild(ground,1);
		_groundSprites->addObject(ground);
	}

	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bee010.png","bee010.plist","bee01.ExportJson");
	beeArmature = CCArmature::create("bee01");
	beeArmature->getAnimation()->play("BEE");
	beeArmature->setPosition(ccp(screenSize.width/4,screenSize.height/2));
	beeArmature->setAnchorPoint(ccp(0.5,0.5));
	this->addChild(beeArmature,1);

	score = 0;
	char string[32];
	sprintf(string, "%d", score);
	pLabel = CCLabelBMFont::create(string, "font.fnt", screenSize.width);//CCLabelTTF::create(string, "fonts/MarkerFelt.ttf", 30);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 2);


	pReady = CCLabelTTF::create("Get Ready", "fonts/MarkerFelt.ttf", 50);

	// position the label on the center of the screen
	pReady->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height-(visibleSize.height/4)));

	// add the label as a child to this layer
	this->addChild(pReady, 2);

	pTap = CCLabelTTF::create("Tap to flap", "fonts/MarkerFelt.ttf", 50);

	// position the label on the center of the screen
	pTap->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + (visibleSize.height/4)));

	// add the label as a child to this layer
	this->addChild(pTap, 2);


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	createSaveMeLayer();

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(HelloWorld::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//pStoreLayer=StoreLayer::getInstance()->getLayer();
	StoreLayer::getInstance()->setGameLayer(this);
	StoreLayer::getInstance()->setVisible(false);
	this->addChild(StoreLayer::getInstance(),10);

	scheduleUpdate();
	setTouchEnabled(true);

}

void HelloWorld::createSaveMeLayer()
{
	progressTimer = CCProgressTimer::create( CCSprite::create("bee.png") );
	if ( progressTimer != NULL )
	{
		progressTimer->setType(kCCProgressTimerTypeBar);
		progressTimer->setTag(kTagOfSaveMeBar);
		progressTimer->setMidpoint(ccp(0, 0));
		progressTimer->setBarChangeRate(ccp(1, 0));
		progressTimer->setPercentage(100);
		progressTimer->setPosition(ccp(screenSize.width/2, (screenSize.height/2)-(progressTimer->getContentSize().height)));
		progressTimer->setVisible(false);
		this->addChild(progressTimer,9);
	}

	CCLayer *pSaveMeLayer=CCLayer::create();
	pSaveMeLayer->setTag(kTagOfSaveMeLayer);
	CCSprite *bg = CCSprite::create("popup.png");
	bg->setPosition(ccp(screenSize.width/2,screenSize.height/2));
	pSaveMeLayer->addChild(bg);

	//CCProgressTimer* fuelBar; 
	//fuelBar = CCProgressTimer::create(CCSprite::create("vishal.png" ));
	//// Set this progress bar object as kCCProgressTimerTypeBar (%)
	//fuelBar->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
	////fuelBar->setAnchorPoint(ccp(0,0));
	//fuelBar->setBarChangeRate(ccp(1,0)); // To make width 100% always
	//fuelBar->setPosition(bg->getContentSize().width/2,bg->getContentSize().height/2+fuelBar->getContentSize().height);
	//pSaveMeLayer->addChild(fuelBar,1);

	CCMenuItem *pCloseItem = CCMenuItemFont::create(
                                        "Save Me",
                                        this,
                                        menu_selector(HelloWorld::saveMeCallback) );

	pCloseItem->setPosition(ccp((screenSize.width/2),+(screenSize.height/2)));
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	pSaveMeLayer->addChild(pMenu, 1);

	pSaveMeLayer->setVisible(false);
	this->addChild(pSaveMeLayer,8);
}
HelloWorld::~HelloWorld()
{
	delete _pipes;
	_pipes = NULL;
	delete world;
	world = NULL;
	CC_SAFE_RELEASE(_groundSprites);
	//delete m_debugDraw;
}

void HelloWorld::initPhysics() 
{
	b2Vec2 gravity;
	gravity.Set(0.0f, kGravity);
	world = new b2World(gravity);
	// Do we want to let bodies sleep?
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	// world->SetContactListener(_collisionListener);

	world->SetContactListener(this);

	//m_debugDraw = new GLESDebugDraw( PTM_RATIO );
	//world->SetDebugDraw(m_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	// flags += b2Draw::e_jointBit;
	// flags += b2Draw::e_aabbBit;
	// flags += b2Draw::e_pairBit;// flags += b2Draw::e_centerOfMassBit;
	//m_debugDraw->SetFlags(flags);

	//adde bee body
	this->addPlatform();
	this->addBox(ccp((screenSize.width/4),screenSize.height/2),beeArmature->getContentSize().width/2,beeArmature->getContentSize().height/2);

	_pipes	= new vector<Obstacle*>;

	Obstacle * csprite;
	for (int i = 0; i < kNoOfPipes; i++) 
	{
		CCSprite* topSprite = CCSprite::create("pipe.png");
		topSprite->setFlipY(true);
		csprite= new Obstacle(topSprite,CCSprite::create("pipe.png"));

		float randomNo = randomFloat(0,11);
		float x = screenSize.width + (kDistanceBetweenObstacle*i);
		float y = (screenSize.height/4) + ((kGapBetweenObstacle/4)*randomNo);
		csprite->initObstaclePos(ccp(x,y+kGapBetweenObstacle),ccp(x,y),world);

		//csprite->initPhysicsBody(world);

		this->addChild(csprite->gettopSprite(),0);
		this->addChild(csprite->getbottomSprite(),0);

		_pipes->push_back(csprite);
	}


	//this->addBall(ccp(screenSize.width/2,screenSize.height),10);
}

void HelloWorld::BeginContact(b2Contact* contact) {
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

	if((int)bodyA->GetUserData() == kSensorBody || (int)bodyB->GetUserData() == kSensorBody)
	{
		HelloWorld::score++;
	}else
	{
		HelloWorld::collisionFlag = false;
		if(!saveMeFlag)
		{
			progressTimer->setVisible(true);
			progressTimer->setPercentage(100);
			setcurruntState(kGameSaveMe);
			this->getChildByTag(kTagOfSaveMeLayer)->setVisible(true);
			//this->getChildByTag(kTagOfSaveMeLayer)->runAction(CCEaseBounce::create(CCMoveBy::create(1.0, ccp(0,screenSize.height/2))));
			scroll=0;
		}
		//CCTransitionFade * trans = CCTransitionFade::create( 0.5f, GameOver::scene(), ccBLACK );
		//CCDirector::sharedDirector() -> replaceScene( trans );	
	}
}

void HelloWorld::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)  {
    
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();
	
}

void HelloWorld::EndContact(b2Contact* contact) {
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

	if((int)bodyA->GetUserData() != kSensorBody || (int)bodyB->GetUserData() != kSensorBody)
	{
		HelloWorld::collisionFlag=true;
	}
}

void HelloWorld::draw()
{
	//
	// IMPORTANT:
	// This is only for debug purposes
	// It is recommend to disable it

	/*CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();*/

}

void HelloWorld::GameOver()
{
	StoreLayer::getInstance()->removeFromParentAndCleanup(false);
	HelloWorld::collisionFlag = true;
	CCTransitionFade * trans = CCTransitionFade::create( 0.5f, GameOver::scene(), ccBLACK );
	CCDirector::sharedDirector() -> replaceScene( trans );
}

void HelloWorld::update(float dt)
{
	int32 velocityIterations = 8;
	int32 positionIterations = 6;


	/*Loop ground*/
	CCSprite* tempSprite;
	for (int i = 0; i < _groundSprites->count(); i++)
	{
		tempSprite = (CCSprite* ) _groundSprites->objectAtIndex(i);
		tempSprite->setPositionX(tempSprite->getPositionX()-(scroll*dt));

		if(tempSprite->getPositionX()<-(tempSprite->getContentSize().width))
		{
			tempSprite->setPositionX(tempSprite->getContentSize().width);
		}
	}
	float rotation;
	switch (getcurruntState())
	{
	case kGameReady:

		break;
	case kGamePlay:
		
		world->Step(dt, velocityIterations, positionIterations);
		if (beeBody->GetLinearVelocity().y > kMaxVelocity) 
		{
			b2Vec2 adjustVelocity;
			adjustVelocity.Set(beeBody->GetLinearVelocity().x, kMaxVelocity);
			beeBody->SetLinearVelocity(adjustVelocity);
		}

		rotation = ((beeBody->GetLinearVelocity().y + kMaxVelocity) / (2*kMaxVelocity)) * M_2_PI;
		//beeArmature->setRotation(-1*CC_RADIANS_TO_DEGREES(rotation-M_1_PI/2));
		beeArmature->setPositionX(beeBody->GetPosition().x*PTM_RATIO);
		beeArmature->setPositionY(beeBody->GetPosition().y*PTM_RATIO);

		Obstacle* pipe;
		for (int i = 0; i < _pipes->size(); i++)
		{
			pipe =  _pipes->at(i);

			pipe->changePos(ccp(pipe->gettopPos().x-(scroll*dt),pipe->gettopPos().y),ccp(pipe->getbottomPos().x-(scroll*dt),pipe->getbottomPos().y));

			if(pipe->gettopPos().x<-pipe->gettopSprite()->getContentSize().width)
			{
				float randomNo = randomFloat(0,11);
				float y = (screenSize.height/4) + ((kGapBetweenObstacle/4)*randomNo);
				float x =  screenSize.width ;
				pipe->changePos(ccp(x,y+kGapBetweenObstacle),ccp(x,y));
			}

			// check collision with pipes

			CCRect beeRect = CCRectMake(
				beeArmature->getPosition().x - (beeArmature->getContentSize().width/4),
				beeArmature->getPosition().y - (beeArmature->getContentSize().height/4),
				beeArmature->getContentSize().width/2,
				beeArmature->getContentSize().height/2); 
			CCRect topRect = pipe->gettopSprite()->boundingBox();
			CCRect bottomRect = pipe->getbottomSprite()->boundingBox();
			if((beeRect.intersectsRect(topRect)||beeRect.intersectsRect(bottomRect))&&!saveMeFlag)
			{
				scroll=0;
				setcurruntState(kGameOver);
			}

		}
		break;
	case kGameOver:
		world->Step(dt, velocityIterations, positionIterations);
		if (beeBody->GetLinearVelocity().y > kMaxVelocity) 
		{
			b2Vec2 adjustVelocity;
			adjustVelocity.Set(beeBody->GetLinearVelocity().x, kMaxVelocity);
			beeBody->SetLinearVelocity(adjustVelocity);
		}

		rotation = ((beeBody->GetLinearVelocity().y + kMaxVelocity) / (2*kMaxVelocity)) * M_2_PI;
		beeArmature->setRotation(-1*CC_RADIANS_TO_DEGREES(rotation-M_1_PI/2));
		beeArmature->setPositionX(beeBody->GetPosition().x*PTM_RATIO);
		beeArmature->setPositionY(beeBody->GetPosition().y*PTM_RATIO);
		
		break;
	case kGameSaveMe:
		if(!StoreLayer::getInstance()->isVisible())
		progressTimer->setPercentage(progressTimer->getPercentage()-1);
		
		if(progressTimer->getPercentage()<=0)
		{
			GameOver();
		}
		break;
	}


	char string[32];
	sprintf(string, "%d", score);
	pLabel->setString(string);

}



void HelloWorld::addPlatform()
{
	CCSprite* ground = (CCSprite *) _groundSprites->objectAtIndex(0);
	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position=b2Vec2((screenSize.width*0.5)/PTM_RATIO,(ground->getContentSize().height/2)/PTM_RATIO);

	b2Body * body = world->CreateBody(&bodyDef);
	//bodyDef.position.Set(160.0f/PTM_RATIO,240.0f/PTM_RATIO);
	//define shape
	b2PolygonShape box;
	box.SetAsBox((ground->getContentSize().width/2) /PTM_RATIO, (ground->getContentSize().height/2) / PTM_RATIO);
	//Define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 2;
	fixtureDef.restitution = 0;
	body->CreateFixture(&fixtureDef);
}

void HelloWorld::addBox(CCPoint point,float w,float h)
{
	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(point.x/PTM_RATIO,point.y/PTM_RATIO);
	//b2Body * body = world->CreateBody(&bodyDef);
	beeBody = world->CreateBody(&bodyDef);
	//beeBody->SetUserData("bee");

	//define shape
	b2PolygonShape box;
	box.SetAsBox(w/2/PTM_RATIO , h/2/PTM_RATIO );
	//Define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 1.15;
	fixtureDef.restitution = 0;
	beeBody->CreateFixture(&fixtureDef);
	//beeBody->CreateFixture(&fixtureDef);
}

void HelloWorld::addBall(CCPoint point,float radius)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//or make it static bodyDef.type = b2_staticBody;
	bodyDef.position.Set(point.x/PTM_RATIO,point.y/PTM_RATIO);
	b2Body * body = world->CreateBody(&bodyDef);
	//body->SetUserData("bee");
	//create circle shape
	b2CircleShape circle;
	circle.m_radius = radius/PTM_RATIO;
	//define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1;
	fixtureDef.restitution = 0.7;
	fixtureDef.friction = 0.4;
	body->CreateFixture(&fixtureDef);
}


void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	//Add a new body/atlas sprite at the touched location
	CCSetIterator it;
	CCTouch* touch;

	for( it = touches->begin(); it != touches->end(); it++) 
	{
		touch = (CCTouch*)(*it);

		if(!touch)
			break;
		CCPoint location = touch->getLocation();
		b2Vec2 gravity;
		switch (getcurruntState())
		{
		case kGameReady:
			pTap->setVisible(false);
			pReady->setVisible(false);
			initPhysics();
			setcurruntState(kGamePlay);
			if(beeArmature->getPositionY() < screenSize.height)
			{
				gravity.Set(beeBody->GetLinearVelocity().x,kMaxVelocity);
				beeBody->SetLinearVelocity(gravity);
			}
			break;
		case kGamePlay:

			if(beeArmature->getPositionY() < screenSize.height)
			{
				gravity.Set(beeBody->GetLinearVelocity().x,kMaxVelocity);
				beeBody->SetLinearVelocity(gravity);
			}	
			break;
		case kGameOver:

			break;
		}

	}
}


void HelloWorld::saveMeCallback(CCObject* pSender)
{
	int coin = CCUserDefault::sharedUserDefault()->getIntegerForKey(kKeyForInitCoin.getCString(),kInitCoin);
	progressTimer->setVisible(false);
	if(coin==0||coin<0)
	{
		StoreLayer::getInstance()->setVisible(true);
		StoreLayer::getInstance()->customOnEnter();
	}else
	{
		
		saveMeFlag=true;
		/* CCDelayTime * delayAction = CCDelayTime::create( 5 );
		 CCCallFunc * callFunc = CCCallFunc::create( this, callfunc_selector( HelloWorld::flipBoolCallback ));
		 this -> runAction( CCSequence::createWithTwoActions( delayAction, callFunc ) );*/
		this->scheduleOnce(schedule_selector(HelloWorld::flipBoolCallback), 3);
		scroll = kScrollSpeed;
	
		setcurruntState(kGamePlay);
		CCActionInterval* action1 = CCBlink::create(3, 20);
		beeArmature->runAction(action1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(kKeyForInitCoin.getCString(),coin-1);
		CCUserDefault::sharedUserDefault()->flush();
		_hud->setString(coin-1);
	}
	
	this->getChildByTag(kTagOfSaveMeLayer)->setVisible(false);
	
}

void HelloWorld::flipBoolCallback(float dt)
{
	saveMeFlag=false;
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
