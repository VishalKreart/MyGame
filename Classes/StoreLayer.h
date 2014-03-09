#ifndef STORELAYER_h
#define STORELAYER_h
#include "cocos2d.h"
#include "Store/StoreManager.h"

class HelloWorld;
class StoreLayer : public cocos2d::CCLayerColor  , public PurchaseListener
{
private:
    StoreLayer();
	~StoreLayer();
	static StoreLayer* m_StoreLayer;
	static CCLayer *m_pLayer;
	static bool m_IsInitialized;
	HelloWorld *gameLayer;
public:

    static StoreLayer* getInstance();
	static StoreLayer* create();
    static void CoinPurchaseCallback(const char *pText);
	static void Destroy();
	CCLayer* getLayer();
   	void customOnEnter();
	void customOnExit();
    virtual bool init();  

	void LoadAssets();
	void UnloadAssets();
	void DrawStoreLayer();
	void ExitCallback(CCObject* pSender);
	void OnBuyClickedCallback(CCObject* pSender);
	CCRect GetFrameBound(int frameID);
	void setGameLayer(HelloWorld *gamelayer);


	void OnPurchaseEvent();


private:
	
	CCPoint screen_mid;

};

#endif
