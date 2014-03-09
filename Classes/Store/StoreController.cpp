/*
 * StoreController.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: Vikas Patidar
 */

#include "StoreController.h"
#include "StoreManager.h"
#include "cocos2d.h"

USING_NS_CC;

bool StoreController::m_bIsStoreInitialized = false;
bool StoreController::m_bIsRunning = false;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <string>

using namespace std;

extern "C"
{
	JNIEXPORT void JNICALL Java_com_billing_BillingManager_onPurchaseSuccess(JNIEnv * env, jobject obj, jstring jItemId)
	{
		StoreController::m_bIsRunning = false;
		string itemId = JniHelper::jstring2string(jItemId);
		CCLOG("%s was just purchased", itemId.c_str());
		StoreManager::Instance()->OnPurchaseSucceed(itemId.c_str());
	}

	JNIEXPORT void JNICALL Java_com_billing_BillingManager_onPurchaseError(JNIEnv * env, jobject obj, jstring jErrorMessage)
	{
		StoreController::m_bIsRunning = false;
		string error = JniHelper::jstring2string(jErrorMessage);
		CCLOG("Error : %s", error.c_str());
		StoreManager::Instance()->OnPurchaseError(error.c_str());
	}

	JNIEXPORT void JNICALL Java_com_billing_BillingManager_onPurchaseCancel(JNIEnv * env, jobject obj)
	{
		StoreController::m_bIsRunning = false;
		CCLOG("User canceled purchase");
		StoreManager::Instance()->OnPurchaseCanceled();
	}

	JNIEXPORT void JNICALL Java_com_billing_BillingManager_onPurchaseSetup(JNIEnv * env, jobject obj)
	{
		StoreController::m_bIsStoreInitialized = true;
		CCLOG("purchase setup finished");
	}

	JNIEXPORT void JNICALL Java_com_billing_BillingManager_onPurchaseRestore(JNIEnv * env, jobject obj, jstring jItemIds)
	{
		StoreController::m_bIsRunning = false;
		string itemIds = JniHelper::jstring2string(jItemIds);
		CCLOG("purchase for %s items just restored", itemIds.c_str());
		StoreManager::Instance()->OnPurchaseRestored(itemIds.c_str());
	}
}
#endif

StoreController::StoreController() {
}

StoreController::~StoreController() {
}

void StoreController::openStore(void) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	if (JniHelper::getStaticMethodInfo(minfo, "com/billing/BillingManager", "open", "()V")) {
		 minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
#endif
}

void StoreController::closeStore(void) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	if (JniHelper::getStaticMethodInfo(minfo, "com/billing/BillingManager", "close", "()V")) {
		 minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
	m_bIsRunning = false;
#endif
}

void StoreController::buyItem(const char* itemId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(m_bIsStoreInitialized && !m_bIsRunning)
	{
		m_bIsRunning = true;
		JniMethodInfo minfo;
		if (JniHelper::getStaticMethodInfo(minfo, "com/billing/BillingManager", "buyMarketItem", "(Ljava/lang/String;)V")) {
			jstring jItemId = minfo.env->NewStringUTF(itemId);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jItemId);
		}
	}
#endif
}

void StoreController::restore(void) {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	if (JniHelper::getStaticMethodInfo(minfo, "com/billing/BillingManager", "restore", "()V")) {
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
	#endif
}
