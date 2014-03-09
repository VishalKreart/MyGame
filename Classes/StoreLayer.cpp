#include "StoreLayer.h"
#include "Store/StoreConfig.h"
#include "Store/StoreManager.h"
#include "HelloWorldScene.h"

USING_NS_CC;

StoreLayer*	StoreLayer::m_StoreLayer	= NULL;
CCLayer* StoreLayer::m_pLayer=NULL;
bool StoreLayer::m_IsInitialized=false;

StoreLayer::StoreLayer()
{
	LoadAssets();
}

StoreLayer::~StoreLayer()
{
	UnloadAssets();
}

StoreLayer* StoreLayer::getInstance()
{
	if(!m_IsInitialized)
	{
	m_StoreLayer=new StoreLayer();
	m_StoreLayer->create();
	m_IsInitialized=true;
	}
	return (m_StoreLayer);
}

StoreLayer* StoreLayer::create()
{
    m_pLayer =(StoreLayer*)m_StoreLayer;
	if(m_StoreLayer  && m_StoreLayer->init())
	{
	m_StoreLayer->retain();
  	return m_StoreLayer;
	}
	return NULL;
}


CCLayer* StoreLayer::getLayer()
{
	return m_pLayer;
}


void StoreLayer::UnloadAssets()
{

}

void StoreLayer::Destroy()
{
	m_StoreLayer->removeFromParentAndCleanup(false);
	delete  m_StoreLayer;
}

void StoreLayer::LoadAssets()
{
	 
}

bool StoreLayer::init()
{
    bool bRet = false;
    do
    {
    if( !CCLayerColor::initWithColor(ccc4(82, 0, 125,0)) ) //RGBA
    {
      return false;
    }
	DrawStoreLayer();
	//StoreManager::Instance()->SetPurchaseListener(this);
	bRet = true;
    } while (0);

    return bRet;
}

void StoreLayer::setGameLayer(HelloWorld *gamelayer)
{
	gamelayer=gamelayer;
}

void StoreLayer::DrawStoreLayer()
{
	
	screen_mid = CCPointMake(CCDirector::sharedDirector()->getWinSize().width*0.5f,
			     CCDirector::sharedDirector()->getWinSize().height*0.5f);

	CCSprite* popUp = CCSprite::create("popup.png");
	popUp->setPosition(screen_mid);
	m_pLayer->addChild(popUp,0);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *buyItem = CCMenuItemImage::create(
                                        "btn_play.png",
                                        "btn_play_focus.png",
                                        this,
										menu_selector(StoreLayer::OnBuyClickedCallback));
	buyItem->setPosition((size.width/2),(size.height/2));
	buyItem->setTag(0);

	CCMenuItemImage *closeButton = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
										menu_selector(StoreLayer::OnBuyClickedCallback));

	closeButton->setPosition((size.width/2)+(popUp->getContentSize().width/2),(size.height/2)+(popUp->getContentSize().height/2));
	closeButton->setTag(1);
	CCMenu* pMenu = CCMenu::create(buyItem,closeButton, NULL);
	pMenu->setPosition(CCPointZero);
	m_pLayer->addChild(pMenu, 0);
}


void StoreLayer::customOnEnter()
{
	StoreManager::Instance()->OpenStore();
	StoreManager::Instance()->SetPurchaseListener(this);
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority -10 ,true);
}
void StoreLayer::customOnExit()
{
	if(this->isVisible())
	{
		StoreManager::Instance()->CloseStore();
		this->setVisible(false);
		gameLayer->GameOver();
		//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}

}

void StoreLayer::OnPurchaseEvent()
{
    ExitCallback(NULL);
}


void StoreLayer::ExitCallback(CCObject* pSender)
{
	CCLayer *p_Layer=(CCLayer*)this->getParent();
	StoreLayer::getInstance()->customOnExit();
}

void StoreLayer::CoinPurchaseCallback(const char *pLable)
{

}

void StoreLayer:: OnBuyClickedCallback(CCObject* pSender)
{
			switch(((CCNode*)pSender)->getTag())
			{
				case 0: //Booster Pack
				StoreManager::Instance()->BuyItem(StoreConfig::COIN_PACK_IDS[StoreConfig::kTagCoinPackBoost].c_str());
				break;
				case 1: //Mega Pack
				ExitCallback(NULL);
				break;
				case 2: //Ultra Pack
				StoreManager::Instance()->BuyItem(StoreConfig::COIN_PACK_IDS[StoreConfig::kTagCoinPackUltra].c_str());
				break;
				case 3: //Ultra Ultra Pack
				break;
				case 4: //Exit Btn
				ExitCallback(NULL);
				return;
				break;
			}
}
