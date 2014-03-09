#ifndef __STORE_MANAGER_H__
#define __STORE_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class PurchaseListener;
class StoreManager
{
private:
	StoreManager();
	StoreManager(StoreManager* const);
    void operator=(StoreManager* const);

public:
	~StoreManager();
	static StoreManager* Instance(void);
	void BuyItem(const char* itemId);

	void OnPurchaseSucceed(const char*);
	void OnPurchaseCanceled(void);
	void OnPurchaseError(const char*);
	void OnPurchaseRestored(const char*);

	void SetPurchaseListener(PurchaseListener*);
	void OpenStore(void);
	void CloseStore(void);

	bool CanDismiss(void);

private:
	static StoreManager* m_pStoreManager;
	static bool m_bIsInitialized;
	bool m_bCanDismiss;
	PurchaseListener* m_pPurchaseListener;
};

class PurchaseListener
{
public:
	virtual ~PurchaseListener() {}
	virtual void OnPurchaseEvent(void) = 0;
};
#endif
