#include "CCHelper.h"
#include "cocos2d.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../cocos2dx/platform/android/jni/JniHelper.h"
#include "../../cocos2dx/platform/CCCommon.h"
#endif

USING_NS_CC;

using namespace std;

void CCHelper::OpeUri(const char* pszUri)
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		ShellExecuteA(NULL, "open", pszUri, NULL, NULL, SW_SHOWNORMAL);
	}
	#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;

		if(JniHelper::getStaticMethodInfo(minfo, "com/util/Helper",  "openUri", "(Ljava/lang/String;)V"))
		{
			jstring url = minfo.env->NewStringUTF(pszUri);
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, url);
			minfo.env->DeleteLocalRef(minfo.classID);
			minfo.env->DeleteLocalRef(url);
		}
	}
	#endif
}

void CCHelper::OpeStoreUri()
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		//ShellExecuteA(NULL, "open", pszUri, NULL, NULL, SW_SHOWNORMAL);
	}
	#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;

		if(JniHelper::getStaticMethodInfo(minfo, "com/util/Helper",  "openStoreUri", "()V"))
		{
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
			minfo.env->DeleteLocalRef(minfo.classID);
		}
	}
	#endif
}



string CCHelper::GetVersion(void)
{
	string sVersion("1.0");

	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;
		if(JniHelper::getStaticMethodInfo(minfo, "com/util/Helper",  "getVersion", "()Ljava/lang/String;"))
		{
			jstring str = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
			sVersion = JniHelper::jstring2string(str);
			minfo.env->DeleteLocalRef(minfo.classID);
			minfo.env->DeleteLocalRef(str);
		}
	}
	#endif
	return sVersion;
}

void CCHelper::RateApp(void)
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;
		if(JniHelper::getStaticMethodInfo(minfo, "com/util/Helper",  "openPlayStore", "()V"))
		{
			minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
			minfo.env->DeleteLocalRef(minfo.classID);
		}
	}
	#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		const char* pszUri = "http://windows.microsoft.com/en-IN/windows-8/apps";
		ShellExecuteA(NULL, "open", pszUri, NULL, NULL, SW_SHOWNORMAL);
	}
	#endif
}

void CCHelper::ShowAd(void)
{
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;
		if(JniHelper::getMethodInfo(minfo, "com/util/AdMobHelper", "onShowAd", "()V"))
		{
			minfo.env->CallObjectMethod(minfo.classID, minfo.methodID);
			minfo.env->DeleteLocalRef(minfo.classID);
		}
	}
/*	#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		const char* pszUri = "http://windows.microsoft.com/en-IN/windows-8/apps";
		ShellExecuteA(NULL, "open", pszUri, NULL, NULL, SW_SHOWNORMAL);
	}*/
	#endif
}


void CCHelper::ShowInhouseAd(void)
{

	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		JniMethodInfo minfo;
		if(JniHelper::getMethodInfo(minfo, "com/twist/CutTheBox", "startAds", "()V"))
		{
			CCLOG("==================INside ShowInhouseAd===============");
			minfo.env->CallObjectMethod(minfo.classID, minfo.methodID);
			minfo.env->DeleteLocalRef(minfo.classID);
			CCLOG("==================OutSide InhouseAd===============");
		}
	}
/*	#elif(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		const char* pszUri = "http://windows.microsoft.com/en-IN/windows-8/apps";
		ShellExecuteA(NULL, "open", pszUri, NULL, NULL, SW_SHOWNORMAL);
	}*/
	#endif
}
