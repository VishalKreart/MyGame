#include "../Store/StoreManager.h"
#include "../Store/StoreConfig.h"


USING_NS_CC;
using namespace std;
#include "StoreController.h"

StoreManager* StoreManager::m_pStoreManager = NULL;
bool StoreManager::m_bIsInitialized = false;

StoreManager::StoreManager() {
	m_pPurchaseListener = NULL;
	m_bCanDismiss = false;
}

StoreManager::~StoreManager() {
	m_bIsInitialized = false;
}

StoreManager* StoreManager::Instance(void) {
	if (!m_bIsInitialized) {
		m_pStoreManager = new StoreManager();
		m_bIsInitialized = true;
	}
	return (m_pStoreManager);
}

void StoreManager::OpenStore(void)
{
	StoreController::openStore();
}

void StoreManager::CloseStore(void) {
	if (m_bCanDismiss)
	{
		StoreController::closeStore();
	}
}

bool StoreManager::CanDismiss(void) {
	return (m_bCanDismiss);
}

void StoreManager::BuyItem(const char* itemId)
{
	CCLOG("INside StoreManager::BuyItem %s",itemId);
	m_bCanDismiss = false;

	StoreController::buyItem(itemId);
}

void StoreManager::OnPurchaseSucceed(const char* itemKey)
{
	m_bCanDismiss = true;
	// Remove Store Layer or Scene
	// do your stuff here.
	string itemId(itemKey);

	int nCoins = 0;
	for (int item = 0; item < MAX_COIN_PACKS; item++) 
	{
		if (itemId.compare(StoreConfig::COIN_PACK_IDS[item]) == 0) 
		{
			char pCoinKey[256];
			sprintf(pCoinKey, StoreConfig::m_sCoinKey, item);

			if (item == StoreConfig::kTagAdfreeVersion && !CCUserDefault::sharedUserDefault()->getBoolForKey("ISAdfreeVersion")) 
			{
				CCLOG("***********AD FREE Purchased is ********************");
				CCUserDefault::sharedUserDefault()->setBoolForKey("ISAdfreeVersion", true);

				if (m_pPurchaseListener)
				{
				m_pPurchaseListener->OnPurchaseEvent();
				}

				return;
			} else 
			{
				nCoins = atoi(StoreConfig::COIN_PACK_COINS[item].c_str());
				CCLOG("Coins Purchased is %d", nCoins);
				/*TMInApp::getinstance()->setPurchasedCoins(nCoins);
				TMInApp::getinstance()->setTotalStarsEarned(0);
				TMInApp::getinstance()->UpdateTotalCoins();
				CCUserDefault::sharedUserDefault()->setIntegerForKey(
						TOTALCOINSEARNED,
						TMInApp::getinstance()->getTotalCoinsEarned());
				TMInApp::getinstance()->setPurchasedCoins(0);*/
				//StoreLayer::getInstance()->customOnExit();

				if (m_pPurchaseListener)
				{
				m_pPurchaseListener->OnPurchaseEvent();
				}

			return;
			}
		}
	}

}

void StoreManager::OnPurchaseRestored(const char* itemKey) {
	m_bCanDismiss = true;

	std::string itemId(itemKey);

	int nCoins = 0;
	for (int item = 0; item < MAX_COIN_PACKS; item++) {
		if (itemId.compare(StoreConfig::COIN_PACK_IDS[item]) == 0) {
			char pCoinKey[256];
			sprintf(pCoinKey, StoreConfig::m_sCoinKey, item);

			if (item == StoreConfig::kTagAdfreeVersion
					&& !CCUserDefault::sharedUserDefault()->getBoolForKey(
							"ISAdfreeVersion")) {
				CCLOG("***********AD FREE Purchased is ********************");
				CCUserDefault::sharedUserDefault()->setBoolForKey("ISAdfreeVersion", true);

				return;
			} else {
				nCoins = atoi(StoreConfig::COIN_PACK_COINS[item].c_str());
				CCLOG("Coins Purchased is %d", nCoins);
				/*TMInApp::getinstance()->setPurchasedCoins(nCoins);
				TMInApp::getinstance()->setTotalStarsEarned(0);
				TMInApp::getinstance()->UpdateTotalCoins();
				CCUserDefault::sharedUserDefault()->setIntegerForKey(
						TOTALCOINSEARNED,
						TMInApp::getinstance()->getTotalCoinsEarned());
				TMInApp::getinstance()->setPurchasedCoins(0);*/
				//StoreLayer::getInstance()->customOnExit();

			return;
			}
		}
	}

}
void StoreManager::OnPurchaseCanceled(void)
{
	// Remove Store Layer or Scene
	if (m_pPurchaseListener) {
			m_pPurchaseListener->OnPurchaseEvent();
		}
}
void StoreManager::OnPurchaseError(const char* error) {
	m_bCanDismiss = true;
	if (m_pPurchaseListener) {
		m_pPurchaseListener->OnPurchaseEvent();
	}
}
void StoreManager::SetPurchaseListener(PurchaseListener* pListener) {
	m_pPurchaseListener = pListener;
}
